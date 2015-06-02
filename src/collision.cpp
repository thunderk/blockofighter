#include <stdlib.h>
#include <math.h>

#include "object.h"
#include "vector.h"
#include "collision.h"
#include "mesh.h"
#include "3dutils.h"
#include "world.h"
#include "audio.h"

// objectlist *collisionlists[32];
unsigned int collisionlinks[32];

Contact *contacts;
int contactcount;

void initCollisions(void) {
  int i;
  for (i = 0; i < 32; i++) {
    // collisionlists[i] = NULL;
    collisionlinks[i] = 0;
  }
}

/*void addCollisionObject(Object *object, int group){
    objectlist *node = new objectlist;
    node->object = object;
    node->next = collisionlists[group];
    collisionlists[group] = node;
}*/

void addCollisionLink(int source, int target) {
  collisionlinks[source] |= (1 << target);
  if (source != target)
    collisionlinks[target] |= (1 << source);
}

void removeCollisionLink(int source, int target) {
  collisionlinks[source] &= ~(1 << target);
  if (source != target)
    collisionlinks[target] &= ~(1 << source);
}

bool isCollisionLink(int source, int target) {
  if (collisionlinks[source] & (1 << target))
    return true;
  return false;
}

void addCollision(Object *source, Object *target, float *normal,
                  float *contactpoint) {
  if (contactcount == MAXCONTACTS) {
    printf("Too many contacts!\n");
    return;
  }
  Contact *contact = &contacts[contactcount++];
  contact->object1 = source;
  contact->object2 = target;
  vectorCopy(contact->normal, normal);
  vectorCopy(contact->position, contactpoint);
}

#define KINETICFRICTION 0.4

bool handleCollision(Contact *contact) {
  Object *source = contact->object1;
  Object *target = contact->object2;
  float *normal = contact->normal;
  float *contactpoint = contact->position;

  float sourcevelocity[3], targetvelocity[3];
  float sourcecontactpoint[3], targetcontactpoint[3];

  vectorSub(sourcecontactpoint, contactpoint, source->position);
  source->getVelocity(sourcevelocity, sourcecontactpoint);

  if (target == NULL) {
    vectorSet(targetcontactpoint, 0, 0, 0);
    vectorSet(targetvelocity, 0, 0, 0);
  } else {
    vectorSub(targetcontactpoint, contactpoint, target->position);
    target->getVelocity(targetvelocity, targetcontactpoint);
  }

  float deltavelocity[3];
  vectorSub(deltavelocity, sourcevelocity, targetvelocity);
  float dot = vectorDot(deltavelocity, normal);

  // if (fabs(dot) < EPSILON) return false;
  // if (dot > -1.0e-5 && dot < 1.0e-5) return false;
  // if (dot >= 0) return false;
  if (dot > -1.0e-5)
    return false;

  float invmass1;
  invmass1 = source->invmass;

  float invmass2;
  if (target == NULL)
    invmass2 = 0;
  else
    invmass2 = target->invmass;

  float t1;
  if (source->invmomentofinertia == 0) {
    t1 = 0;
  } else {
    float v1[3];
    vectorCross(v1, sourcecontactpoint, normal);
    vectorScale(v1, source->invmomentofinertia);
    float w1[3];
    vectorCross(w1, v1, sourcecontactpoint);
    t1 = vectorDot(normal, w1);
  }

  float t2;
  if (target == NULL || target->invmomentofinertia == 0) {
    t2 = 0;
  } else {
    float v1[3];
    vectorCross(v1, targetcontactpoint, normal);
    vectorScale(v1, target->invmomentofinertia);
    float w1[3];
    vectorCross(w1, v1, targetcontactpoint);
    t2 = vectorDot(normal, w1);
  }

  float denominator = invmass1 + invmass2 + t1 + t2;

  float e = 1.0 - COLLISIONFRICTION;

  float impulsesize = (1 + e) * dot / denominator;

  // printf("%f\n", impulsesize);

  float impulse[3];
  vectorScale(impulse, normal, impulsesize);

  float friction[3];
  vectorScale(friction, normal, vectorDot(deltavelocity, normal));
  vectorAdd(friction, deltavelocity);
  vectorNormalize(friction);
  float frictionsize = 10 * KINETICFRICTION * dot / denominator;
  float maxfrictionsize = 0.1 * vectorLength(deltavelocity);
  if (frictionsize < -maxfrictionsize)
    frictionsize = -maxfrictionsize;
  vectorScale(friction, -frictionsize);
  vectorAdd(impulse, friction);

  if (target != NULL) {
    target->addImpulse(impulse, targetcontactpoint);
    target->calculateStateVariables();
  }

  float speed;
  float speed2[3];

  if (target != NULL && source != NULL) {
    // float kvel[3];
    // source->getVelocity(kvel);
    float k = vectorLength(sourcevelocity) * 0.1;
    // if (k > 1) k = 1;
    speed = -impulsesize * target->invmass * k;
    vectorScale(speed2, impulse, target->invmass * k);
    /*float kvel[3];
        source->getVelocity(kvel);
        float k = 0;//vectorDot(speed2, kvel);
        if (k < EPSILON) k = 0;
        speed *= k;
        vectorScale(speed2, k);
        if (k > 0) */ target->hitForce(speed, speed2, source);
  }

  vectorScale(impulse, -1);
  source->addImpulse(impulse, sourcecontactpoint);
  source->calculateStateVariables();

  // vectorScale(speed, source->invmass);
  if (target != NULL && source != NULL) {
    // float kvel[3];
    // target->getVelocity(kvel);
    float k = vectorLength(targetvelocity) * 0.1;
    // if (k > 1) k = 1;
    speed = -impulsesize * source->invmass * k;
    vectorScale(speed2, impulse, source->invmass * k);
    /*float kvel[3];
        target->getVelocity(kvel);
        float k = 0;//vectorDot(speed2, kvel);
        if (k < EPSILON) k = 0;
        speed *= k;
        vectorScale(speed2, k);
        if (k > 0) */ source->hitForce(speed, speed2, target);
  }

  return true;
}

bool handleLink(ObjectLink *link) {
  if (!link->enabled)
    return false;

  Object *source = link->object1;
  Object *target = link->object2;

  float normal[3];
  float contactpoint1[3], contactpoint2[3];
  source->transformPoint(contactpoint1, link->point1);
  target->transformPoint(contactpoint2, link->point2);

  float diff[3];
  vectorSub(diff, contactpoint1, contactpoint2);
  vectorNormalize(normal, diff);

  float strength = vectorDot(diff, diff);

  if (strength < 1.0e-5)
    return false;

  float sourcevelocity[3], targetvelocity[3];
  float sourcecontactpoint[3], targetcontactpoint[3];

  vectorSub(sourcecontactpoint, contactpoint1, source->position);
  source->getVelocity(sourcevelocity, sourcecontactpoint);

  vectorSub(targetcontactpoint, contactpoint2, target->position);
  target->getVelocity(targetvelocity, targetcontactpoint);

  float deltavelocity[3];
  vectorSub(deltavelocity, sourcevelocity, targetvelocity);
  float dot = vectorDot(deltavelocity, normal);

  // if (fabs(dot) < EPSILON) return false;
  // if (dot > -1.0e-5 && dot < 1.0e-5) return false;
  // if (dot >= 0) return false;
  // if (dot > -1.0e-5) return false;

  float invmass1 = source->invmass;
  float invmass2 = target->invmass;

  float t1;
  if (source->invmomentofinertia == 0) {
    t1 = 0;
  } else {
    float v1[3];
    vectorCross(v1, sourcecontactpoint, normal);
    vectorScale(v1, source->invmomentofinertia);
    float w1[3];
    vectorCross(w1, v1, sourcecontactpoint);
    t1 = vectorDot(normal, w1);
  }

  float t2;
  if (target->invmomentofinertia == 0) {
    t2 = 0;
  } else {
    float v1[3];
    vectorCross(v1, targetcontactpoint, normal);
    vectorScale(v1, target->invmomentofinertia);
    float w1[3];
    vectorCross(w1, v1, targetcontactpoint);
    t2 = vectorDot(normal, w1);
  }

  float denominator = invmass1 + invmass2 + t1 + t2;

  float impulsesize = (dot + strength * 100) / denominator;

  // printf("%f\n", impulsesize);

  float impulse[3];
  vectorScale(impulse, normal, impulsesize);

  target->addImpulse(impulse, targetcontactpoint);
  target->calculateStateVariables();

  vectorScale(impulse, -1);
  source->addImpulse(impulse, sourcecontactpoint);
  source->calculateStateVariables();

  return true;
}

bool checkCollisions(Object *object, float *contactnormal) {
  // bool collision = false;
  int group = object->getCollisionGroup();
  // UNUSED//int groups = collisionlinks[group];
  group = 0;
  int collisions = 0;
  /*float oldmomentum[3];
  vectorCopy(oldmomentum, object->momentum);

  while (groups){
      if (groups & 1){
          objectlist *node = collisionlists[group];
          while (node != NULL){
              Object *object2 = node->object;
              node = node->next;
              if (object != object2){
                  if (object2->geometry->checkCollision(object, contactnormal)){
                      collisions++;
                  }
              }
          }
      }
      group++;
      groups >>= 1;
  }
  /*float temp[3];
  vectorSub(temp, object->momentum, oldmomentum);
  vectorScale(temp, 1.0/DT);
  object->addForce(temp);*/
  // vectorSub(object->
  // vectorCopy(object->momentum, oldmomentum);
  // printf("%i\n", collisions);
  // vectorScale(object->force, 1.0/collisions);
  /*if (collisions > 0){
      vectorScale(object->force, 2.0/vectorLength(object->momentum));
  }*/
  return collisions > 0;
}

/*
 * mass = 0 means infinite mass
 */
/*void collide(float *velocity1, float *velocity2,
                         float mass1, float mass2,
                         float *normal, float *newimpulse){
    float deltavelocity[3];
    vectorSub(deltavelocity, velocity1, velocity2);
    float dot = vectorDot(deltavelocity, normal);
    float massinverse1 = 0;
    float massinverse2 = 0;
    if (mass1 != 0) massinverse1 = 1.0 / mass1;
    if (mass2 != 0) massinverse2 = 1.0 / mass2;
    float impulsesize = -1 * dot / (massinverse1 + massinverse2);
    vectorScale(newimpulse, normal, impulsesize);
    if (dot > 0){
        vectorSet(newimpulse, 0, 0, 0);
    }
}*/

void collide(Object *source, Object *target, float *normal,
             float *contactpoint) {
  /*	float momentum[3];
      source->getMomentum(momentum);

      float sourcevelocity[3], targetvelocity[3];
      float sourcecontactpoint[3], targetcontactpoint[3];

      //source->unTransformPoint(sourcecontactpoint, contactpoint);
      //target->unTransformPoint(targetcontactpoint, contactpoint);
      vectorSub(sourcecontactpoint, contactpoint, source->position);
      vectorSub(targetcontactpoint, contactpoint, target->position);

      source->getVelocity(sourcevelocity);//, sourcecontactpoint);
      float sourcemass = source->getMass();

      target->getVelocity(targetvelocity);//, targetcontactpoint);
      float targetmass = target->getMass();

      float deltavelocity[3];
      vectorSub(deltavelocity, sourcevelocity, targetvelocity);
      float dot = vectorDot(deltavelocity, normal);
      float massinverse1 = 0;
      float massinverse2 = 0;
      if (sourcemass != 0) massinverse1 = 1.0 / sourcemass;
      if (targetmass != 0) massinverse2 = 1.0 / targetmass;

      float t1;
      if (source->invmomentofinertia == 0){
          t1 = 0;
      } else{
          float v1[3];
          vectorCross(v1, sourcecontactpoint, normal);
          vectorScale(v1, 1.0/source->momentofinertia);
          float w1[3];
          vectorCross(w1, v1, sourcecontactpoint);
          t1 = vectorDot(normal, w1);
      }
      //printf("S: %f, %f, %f\n", sourcecontactpoint[0],
     source->momentofinertia, v1);

      float t2;
      if (target->momentofinertia == 0){
          t2 = 0;
      } else{
          float v2[3];
          vectorCross(v2, targetcontactpoint, normal);
          vectorScale(v2, 1.0/target->momentofinertia);
          float w2[3];
          vectorCross(w2, v2, targetcontactpoint);
          t2 = vectorDot(normal, w2);
      }
      //printf("T: %f, %f, %f\n", targetcontactpoint[0],
     target->momentofinertia, v2);


      float divisor;
      divisor = massinverse1 + massinverse2;// + t1 + t2;

      printf("%f, %f, %f, %f : %f\n", massinverse1, massinverse2, t1, t2,
     divisor);

      float impulsesize = -dot / divisor;

      float impulse[3];
      vectorScale(impulse, normal, impulsesize);
      //collide(sourcevelocity, targetvelocity, sourcemass, targetmass, normal,
     impulse);

      //vectorAdd(source->momentum, impulse);

      float *force = impulse;

      //vectorScale(force, 2.0/DT);
      printf("F: %f, %f, %f\n", impulse[0], impulse[1], impulse[2]);

      //float cp[3];
      //vectorSub(cp, contactpoint, source->position);
      //source->addForce(force, sourcecontactpoint);*/
}

bool checkSphereMeshCollision(float *sphereposition, float r, Mesh *mesh,
                              float *normal, float *contactpoint) {
  float linenormal[3];
  float pointnormal[3];
  float maxdist = 0;
  bool planecollision = false;
  bool linecollision = false;
  bool pointcollision = false;

  int i, j;

  for (i = 0; i < mesh->polygoncount; i++) {
    class Polygon *polygon = &mesh->polygons[i];

    float dist = distanceFromPlane(sphereposition, polygon->planenormal,
                                   polygon->planedistance);
    if (dist < r && dist > -r) {
      bool directcollision = true;
      for (j = 0; j < polygon->vertexcount; j++) {
        float *p1 = polygon->vertices[j]->position;
        float *p2 = polygon->vertices[(j + 1) % polygon->vertexcount]->position;
        float *p3 = polygon->vertices[(j + 2) % polygon->vertexcount]->position;
        float v1[3], v2[3];
        vectorSub(v1, p2, p1);

        // Collision for polygon surface
        vectorSub(v2, p3, p2);
        float t1[3];
        vectorProject(t1, v2, v1);
        float norm[3];
        vectorSub(norm, v2, t1);
        vectorNormalize(norm);

        // Collision for polygon edges
        float newpoint[3];
        vectorSub(newpoint, sphereposition, p1);
        float dist2 = vectorDot(newpoint, norm);
        if (dist2 < 0) {
          directcollision = false;
          float projloc = vectorDot(newpoint, v1) / vectorDot(v1, v1);
          if (projloc >= 0 && projloc <= 1) {
            float proj[3];
            vectorScale(proj, v1, projloc);
            float projorth[3];
            vectorSub(projorth, newpoint, proj);
            float l2 = vectorDot(projorth, projorth);
            if (l2 < r * r) {
              vectorNormalize(linenormal, projorth);
              if (dist < 0)
                vectorScale(linenormal, -1);
              linecollision = true;
            }
          }
        }

        // Collision for polygon vertices
        float pointdiff[3];
        vectorSub(pointdiff, sphereposition, p1);
        float l3 = vectorDot(pointdiff, pointdiff);
        if (l3 < r * r) {
          vectorScale(pointnormal, pointdiff, 1.0 / sqrt(l3));
          if (dist < 0)
            vectorScale(pointnormal, -1);
          pointcollision = true;
        }
      }
      if (directcollision) {
        if (dist > maxdist || !planecollision) {
          vectorCopy(normal, polygon->planenormal);
          maxdist = dist;
          planecollision = true;
        }
      }
    }
  }

  if (planecollision) {
    vectorScale(contactpoint, normal, -r);
    vectorAdd(contactpoint, sphereposition);
  } else if (linecollision) {
    vectorScale(contactpoint, linenormal, -r);
    vectorAdd(contactpoint, sphereposition);
    vectorCopy(normal, linenormal);
  } else if (pointcollision) {
    vectorScale(contactpoint, pointnormal, -r);
    vectorAdd(contactpoint, sphereposition);
    vectorCopy(normal, pointnormal);
  } else {
    return false;
  }

  return true;
}

bool checkPointMeshCollision(float *position, Mesh *mesh, float *normal,
                             float *contactpoint) {
  float maxdist = 0;
  bool planecollision = false;

  int i;

  for (i = 0; i < mesh->polygoncount; i++) {
    class Polygon *polygon = &mesh->polygons[i];

    float dist = distanceFromPlane(position, polygon->planenormal,
                                   polygon->planedistance);
    if (dist < 0) {
      bool directcollision = true;
      /*for (j = 0; j < polygon->vertexcount; j++){
          float *p1 = polygon->vertices[j]->position;
          float *p2 = polygon->vertices[(j+1)%polygon->vertexcount]->position;
          float *p3 = polygon->vertices[(j+2)%polygon->vertexcount]->position;
          float v1[3], v2[3];
          vectorSub(v1, p2, p1);

          //Collision for polygon surface
          vectorSub(v2, p3, p2);
          float t1[3];
          vectorProject(t1, v2, v1);
          float norm[3];
          vectorSub(norm, v2, t1);
          vectorNormalize(norm);

          //Collision for polygon edges
          float newpoint[3];
          vectorSub(newpoint, position, p1);
          float dist2 = vectorDot(newpoint, norm);
          if (dist2 < 0) directcollision = false;
      }*/
      if (directcollision) {
        if (dist > maxdist || !planecollision) {
          vectorCopy(normal, polygon->planenormal);
          maxdist = dist;
          planecollision = true;
        }
      }
    } else {
      return false;
    }
  }

  if (planecollision) {
    vectorCopy(contactpoint, position);
  } else {
    return false;
  }

  return true;
}

#define MAXPOLYGONS 1000

struct tracehit {
  float t;
  Polygon *polygon;
};

bool tracePlane(tracehit *result, float *origin, float *ray,
                class Polygon *polygon) {
  float *normal = polygon->planenormal;
  float D = polygon->planedistance;
  float denominator = vectorDot(normal, ray);
  if (denominator == 0) {
    if (vectorDot(normal, origin) > 0)
      result->t = 1000000;
    else
      result->t = -1000000;
    result->polygon = polygon;
    return true;
  }

  float t = -(vectorDot(normal, origin) + D) / denominator;

  result->t = t;
  result->polygon = polygon;

  // if (t < 0 || t > 1) return false;

  return true;
}

Edge *findSharingEdge(class Polygon *p1, class Polygon *p2) {
  // printf("Edges:\n");
  int i, j;
  for (i = 0; i < p1->vertexcount; i++) {
    // printf("%p\n", p1->edges[i]);
    for (j = 0; j < p2->vertexcount; j++) {
      if (p1->edges[i] == p2->edges[j])
        return p1->edges[i];
    }
  }
  return NULL;
}

/*Polygon *findSharingPolygon(Mesh *mesh, class Polygon *p1, class Polygon *p2){
    //printf("Edges:\n");
    int i, j;
    for (i = 0; i < p1->vertexcount; i++){
        //printf("%p\n", p1->edges[i]);
        for (j = 0; j < p2->vertexcount; j++){
            if (p1->edges[i] == p2->edges[j]) return p1->edges[i];
        }
    }
    return NULL;
}*/
Polygon *findNearestPolygon(class Polygon *polygon, float *point) {
  int i;
  float mindist = 0;
  Polygon *nearestpolygon = NULL;
  for (i = 0; i < polygon->edgecount; i++) {
    Edge *edge = polygon->edges[i];
    Polygon *polygon2 = edge->p1;
    if (polygon2 == polygon)
      polygon2 = edge->p2;
    float newdist = distanceFromPlane(point, polygon2->planenormal,
                                      polygon2->planedistance);
    if (newdist > 0)
      return NULL;
    if (mindist == 0 || newdist > mindist) {
      mindist = newdist;
      nearestpolygon = polygon2;
    }
  }
  return nearestpolygon;
}

bool checkEdgeMeshCollision(float *p1, float *p2, Mesh *mesh, float *normal,
                            float *contactpoint) {
  float ray[3];
  vectorSub(ray, p2, p1);

  // UNUSED//float maxdist = 0;
  // UNUSED//bool collision = false;

  int i, j;

  tracehit hits[MAXPOLYGONS];
  int hitcount = 0;

  for (i = 0; i < mesh->polygoncount; i++) {
    class Polygon *polygon = &mesh->polygons[i];

    if (tracePlane(&hits[hitcount], p1, ray, polygon)) {
      hitcount++;
    }
  }

  if (hitcount < 2)
    return false;

  for (i = 1; i < hitcount; i++) {
    for (j = i; j > 0; j--) {
      if (hits[j].t < hits[j - 1].t) {
        float tempt = hits[j].t;
        hits[j].t = hits[j - 1].t;
        hits[j - 1].t = tempt;
        class Polygon *tempp = hits[j].polygon;
        hits[j].polygon = hits[j - 1].polygon;
        hits[j - 1].polygon = tempp;
      } else
        break;
    }
  }

  int negative = -1, positive = -1;

  for (i = 0; i < hitcount; i++) {
    // UNUSED//float t = hits[i].t;
    class Polygon *polygon = hits[i].polygon;

    float dot = vectorDot(ray, polygon->planenormal);

    if (dot > 0 && positive == -1)
      positive = i;
    if (dot < 0)
      negative = i;

    if (dot < 0 && positive != -1)
      return false;
  }

  if (negative == -1 || positive == -1)
    return false;

  /*for (i = 0; i < hitcount; i++){
      float t = hits[i].t;
      class Polygon *polygon = hits[i].polygon;

      float dot = vectorDot(ray, polygon->planenormal);

      printf("%f ", dot);
  }
  printf("\n");*/

  if (hits[negative].t < 0 || hits[positive].t > 1)
    return false;

  Edge *edge2 = findSharingEdge(hits[negative].polygon, hits[positive].polygon);

  // fflush(stdout);
  float cp1[3], cp2[3];
  vectorScale(cp1, ray, hits[negative].t);
  vectorAdd(cp1, p1);
  vectorScale(cp2, ray, hits[positive].t);
  vectorAdd(cp2, p1);

  if (edge2 != NULL) {

    /*float ev1[3];
    vectorSub(ev1, edge2->v2->position, edge2->v1->position);
    vectorCross(normal, ev1, ray);
    vectorScale(normal, vectorDot(normal, hits[positive].polygon->planenormal));
    vectorNormalize(normal);

    float at = (hits[negative].t + hits[positive].t) / 2;
    vectorScale(contactpoint, ray, at);
    vectorAdd(contactpoint, p1);*/

    float dot1 = fabs(vectorDot(ray, hits[negative].polygon->planenormal));
    float dot2 = fabs(vectorDot(ray, hits[positive].polygon->planenormal));

    if (dot1 > dot2) {
      // vectorScale(contactpoint, ray, hits[negative].t);
      // vectorAdd(contactpoint, p1);
      vectorCopy(contactpoint, cp1);
      vectorCopy(normal, hits[positive].polygon->planenormal);
    } else {
      // vectorScale(contactpoint, ray, hits[positive].t);
      // vectorAdd(contactpoint, p1);
      vectorCopy(contactpoint, cp2);
      vectorCopy(normal, hits[negative].polygon->planenormal);
    }
  } else {
    Polygon *polygon = findNearestPolygon(hits[negative].polygon, cp1);
    if (polygon != NULL) {
      /*vectorCopy(contactpoint, cp1);
      vectorAdd(contactpoint, cp2);
      vectorScale(contactpoint, 0.5);*/
      float at = (hits[negative].t + hits[positive].t) / 2;
      vectorScale(contactpoint, ray, at);
      vectorAdd(contactpoint, p1);

      vectorCopy(normal, polygon->planenormal);
    } else {
      return false;
    }
  }

  // shotsound->play();
  return true;
}
