#include "main.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "object.h"
#include "mesh.h"
#include "vector.h"
#include "utils.h"
#include "3dutils.h"
#include "objectfactory.h"
#include "glapi.h"

MeshObject *createPyramid(float width, float height) {
  Mesh *mesh = new Mesh();
  mesh->vertexcount = 5;
  mesh->vertices = new Vertex[5];
  vectorSet(mesh->vertices[0].position, width, 0, 0);
  vectorSet(mesh->vertices[0].normal, 1, 0, 0);
  vectorSet(mesh->vertices[1].position, -width, 0, 0);
  vectorSet(mesh->vertices[1].normal, -1, 0, 0);
  vectorSet(mesh->vertices[2].position, 0, 0, width);
  vectorSet(mesh->vertices[2].normal, 0, 0, 1);
  vectorSet(mesh->vertices[3].position, 0, 0, -width);
  vectorSet(mesh->vertices[3].normal, 0, 0, -1);
  vectorSet(mesh->vertices[4].position, 0, height, 0);
  vectorSet(mesh->vertices[4].normal, 0, 1, 0);

  mesh->polygoncount = 5;
  mesh->polygons = new class Polygon[5];

  mesh->polygons[0].vertexcount = 3;
  mesh->polygons[0].vertices = new Vertex *[3];
  mesh->polygons[0].vertices[0] = &mesh->vertices[4];
  mesh->polygons[0].vertices[1] = &mesh->vertices[0];
  mesh->polygons[0].vertices[2] = &mesh->vertices[3];

  mesh->polygons[1].vertexcount = 3;
  mesh->polygons[1].vertices = new Vertex *[3];
  mesh->polygons[1].vertices[0] = &mesh->vertices[4];
  mesh->polygons[1].vertices[1] = &mesh->vertices[3];
  mesh->polygons[1].vertices[2] = &mesh->vertices[1];

  mesh->polygons[2].vertexcount = 3;
  mesh->polygons[2].vertices = new Vertex *[3];
  mesh->polygons[2].vertices[0] = &mesh->vertices[4];
  mesh->polygons[2].vertices[1] = &mesh->vertices[1];
  mesh->polygons[2].vertices[2] = &mesh->vertices[2];

  mesh->polygons[3].vertexcount = 3;
  mesh->polygons[3].vertices = new Vertex *[3];
  mesh->polygons[3].vertices[0] = &mesh->vertices[4];
  mesh->polygons[3].vertices[1] = &mesh->vertices[2];
  mesh->polygons[3].vertices[2] = &mesh->vertices[0];

  mesh->polygons[4].vertexcount = 4;
  mesh->polygons[4].vertices = new Vertex *[4];
  mesh->polygons[4].vertices[0] = &mesh->vertices[0];
  mesh->polygons[4].vertices[1] = &mesh->vertices[2];
  mesh->polygons[4].vertices[2] = &mesh->vertices[1];
  mesh->polygons[4].vertices[3] = &mesh->vertices[3];

  mesh->polygons[0].smooth = false;
  mesh->polygons[1].smooth = false;
  mesh->polygons[2].smooth = false;
  mesh->polygons[3].smooth = false;
  mesh->polygons[4].smooth = false;

  mesh->createPlanes();

  MeshObject *object = new MeshObject(mesh);
  return object;
}

MeshObject *createSpherePool(float width, float height) {
  int grid = 16;

  Mesh *mesh = new Mesh();
  mesh->vertexcount = (grid + 1) * (grid + 1);
  mesh->vertices = new Vertex[mesh->vertexcount];

  int x, z;
  for (z = 0; z < grid; z++) {
    float pz = (2.0 * z / (grid - 1) - 1) * width;
    for (x = 0; x < grid; x++) {
      float px = (2.0 * x / (grid - 1) - 1) * width;

      // float py = randomf(1);
      float l = sqrt(pz * pz + px * px) * 1;
      if (l > width)
        l = width;
      l = l / width;
      // l = l*l;
      float py = height * (sin(PI * (1.5 + l * 2)) + 1) / 2;
      vectorSet(mesh->vertices[z * grid + x].position, px, py, pz);
    }
  }

  mesh->polygoncount = (grid - 1) * (grid - 1);
  mesh->polygons = new class Polygon[mesh->polygoncount];
  for (z = 0; z < grid - 1; z++) {
    for (x = 0; x < grid - 1; x++) {
      class Polygon *poly = &mesh->polygons[z * (grid - 1) + x];
      poly->vertexcount = 4;
      poly->vertices = new Vertex *[4];

      poly->vertices[0] = &mesh->vertices[z * grid + x + 1];
      poly->vertices[1] = &mesh->vertices[z * grid + x];
      poly->vertices[2] = &mesh->vertices[(z + 1) * grid + x];
      poly->vertices[3] = &mesh->vertices[(z + 1) * grid + x + 1];

      poly->smooth = true;
    }
  }

  mesh->createPlanes();
  mesh->createVertexnormals();

  MeshObject *object = new MeshObject(mesh);
  return object;
}

Mesh *createBox(float x1, float x2, float y1, float y2, float z1, float z2) {
  Mesh *mesh = new Mesh();
  mesh->vertexcount = 8;
  mesh->vertices = new Vertex[8];
  vectorSet(mesh->vertices[0].position, x1, y1, z1);
  vectorSet(mesh->vertices[1].position, x2, y1, z1);
  vectorSet(mesh->vertices[2].position, x1, y2, z1);
  vectorSet(mesh->vertices[3].position, x2, y2, z1);
  vectorSet(mesh->vertices[4].position, x1, y1, z2);
  vectorSet(mesh->vertices[5].position, x2, y1, z2);
  vectorSet(mesh->vertices[6].position, x1, y2, z2);
  vectorSet(mesh->vertices[7].position, x2, y2, z2);

  mesh->polygoncount = 6;
  mesh->polygons = new class Polygon[6];

  // Back
  mesh->polygons[0].vertexcount = 4;
  mesh->polygons[0].vertices = new Vertex *[4];
  mesh->polygons[0].vertices[0] = &mesh->vertices[0];
  mesh->polygons[0].vertices[1] = &mesh->vertices[2];
  mesh->polygons[0].vertices[2] = &mesh->vertices[3];
  mesh->polygons[0].vertices[3] = &mesh->vertices[1];

  // Front
  mesh->polygons[1].vertexcount = 4;
  mesh->polygons[1].vertices = new Vertex *[4];
  mesh->polygons[1].vertices[0] = &mesh->vertices[4];
  mesh->polygons[1].vertices[1] = &mesh->vertices[5];
  mesh->polygons[1].vertices[2] = &mesh->vertices[7];
  mesh->polygons[1].vertices[3] = &mesh->vertices[6];

  // Left
  mesh->polygons[2].vertexcount = 4;
  mesh->polygons[2].vertices = new Vertex *[4];
  mesh->polygons[2].vertices[0] = &mesh->vertices[0];
  mesh->polygons[2].vertices[1] = &mesh->vertices[4];
  mesh->polygons[2].vertices[2] = &mesh->vertices[6];
  mesh->polygons[2].vertices[3] = &mesh->vertices[2];

  // Right
  mesh->polygons[3].vertexcount = 4;
  mesh->polygons[3].vertices = new Vertex *[4];
  mesh->polygons[3].vertices[0] = &mesh->vertices[1];
  mesh->polygons[3].vertices[1] = &mesh->vertices[3];
  mesh->polygons[3].vertices[2] = &mesh->vertices[7];
  mesh->polygons[3].vertices[3] = &mesh->vertices[5];

  // Top
  mesh->polygons[4].vertexcount = 4;
  mesh->polygons[4].vertices = new Vertex *[4];
  mesh->polygons[4].vertices[0] = &mesh->vertices[2];
  mesh->polygons[4].vertices[1] = &mesh->vertices[6];
  mesh->polygons[4].vertices[2] = &mesh->vertices[7];
  mesh->polygons[4].vertices[3] = &mesh->vertices[3];

  // Bottom
  mesh->polygons[5].vertexcount = 4;
  mesh->polygons[5].vertices = new Vertex *[4];
  mesh->polygons[5].vertices[0] = &mesh->vertices[0];
  mesh->polygons[5].vertices[1] = &mesh->vertices[1];
  mesh->polygons[5].vertices[2] = &mesh->vertices[5];
  mesh->polygons[5].vertices[3] = &mesh->vertices[4];

  mesh->createPlanes();
  mesh->createEdges();
  // mesh->createVertexnormals();

  return mesh;
}

float getValueFromString(char *data) {
  while (*data == ' ')
    data++;
  char *enddata = data;
  // char oldchar;
  do {
    enddata++;
    if ((*enddata < '0' || *enddata > '9') && (*enddata != '.'))
      *enddata = 0;
  } while (*enddata != 0);
  float ret = atof(data);
  *enddata = ' ';
  return ret;
}

char *findStringEnd(char *data, char *findstring) {
  return strstr(data, findstring) + strlen(findstring);
}

Mesh *loadAscModel(char *filename, float scale) {
  float zeroOffset[3] = {0.0, 0.0, 0.0};
  return loadAscModel(filename, scale, (float *)zeroOffset);
}

Mesh *loadAscModel(char *filename, float scale, float *offset) {

  Mesh *target = new Mesh();

  FILE *file;
  float x, y, z;

  if ((file = fopen(filename, "rt")) == NULL) {
    printf("Unable to open file %s\n", filename);
    return NULL;
  }
  fseek(file, 0, SEEK_END);
  int size = ftell(file);
  fseek(file, 0, SEEK_SET);
  char *data = (char *)malloc(size * sizeof(char));
  fread(data, size, 1, file);
  fclose(file);
  char *vert = findStringEnd(data, "Vertices:");
  target->vertexcount = (int)getValueFromString(vert);
  char *face = findStringEnd(data, "Faces:");
  target->polygoncount = (int)getValueFromString(face);
  target->vertices = new Vertex[target->vertexcount];
  target->polygons = new class Polygon[target->polygoncount];

  int i;

  vert = findStringEnd(data, "Vertex list:");

  for (i = 0; i < target->vertexcount; i++) {
    vert = findStringEnd(vert, "Vertex");
    vert = findStringEnd(vert, "X:");
    x = getValueFromString(vert) * scale;
    vert = findStringEnd(vert, "Y:");
    y = getValueFromString(vert) * scale;
    vert = findStringEnd(vert, "Z:");
    z = getValueFromString(vert) * scale;
    vectorSet(target->vertices[i].position, x + offset[0], y + offset[1],
              z + offset[2]);
    // recycle variables for texture coordinates
    vert = findStringEnd(vert, "U:");
    x = getValueFromString(vert);
    vert = findStringEnd(vert, "V:");
    y = getValueFromString(vert);
    target->vertices[i].setTexCoords(x, y);
  }
  int vnum;
  face = findStringEnd(data, "Face list:");

  for (i = 0; i < target->polygoncount; i++) {
    face = findStringEnd(face, "Face");
    face = findStringEnd(face, "A:");
    vnum = (int)getValueFromString(face);
    target->polygons[i].vertexcount = 3;
    target->polygons[i].vertices = new Vertex *[3];
    target->polygons[i].vertices[0] = &(target->vertices[vnum]);
    target->polygons[i].vertices[0]->setTexCoords(
        target->vertices[vnum].texcoords[0],
        target->vertices[vnum].texcoords[1]);
    face = findStringEnd(face, "B:");
    vnum = (int)getValueFromString(face);
    target->polygons[i].vertices[1] = &(target->vertices[vnum]);
    target->polygons[i].vertices[1]->setTexCoords(
        target->vertices[vnum].texcoords[0],
        target->vertices[vnum].texcoords[1]);
    face = findStringEnd(face, "C:");
    vnum = (int)getValueFromString(face);
    target->polygons[i].vertices[2] = &(target->vertices[vnum]);
    target->polygons[i].vertices[2]->setTexCoords(
        target->vertices[vnum].texcoords[0],
        target->vertices[vnum].texcoords[1]);
    char *face2 = findStringEnd(face, "Nosmooth");
    char *face3 = findStringEnd(face, "Smoothing");
    if (face2 > face && face2 < face3)
      target->polygons[i].realsmooth = true;
  }
  free(data);
  data = NULL;
  // target->createEdges();
  target->createPlanes();
  target->createVertexnormals();
  // return new MeshObject(target);
  return target;
}

void drawTrophy(void) {
  point2d points[14];

  int width = 3;

  int i = 0;

  points[i].x = 0.0;
  points[i].y = 0.0;
  i++;
  points[i].x = width;
  points[i].y = 0.0;
  i++;
  points[i].x = width - 2;
  points[i].y = 2.0;
  i++;
  points[i].x = width - 2;
  points[i].y = 3.0;
  i++;
  points[i].x = width - 1;
  points[i].y = 4.0;
  i++;
  points[i].x = width - 2;
  points[i].y = 5.0;
  i++;
  points[i].x = width - 2;
  points[i].y = 6.0;
  i++;
  points[i].x = width - 1;
  points[i].y = 8.0;
  i++;
  points[i].x = width;
  points[i].y = 9.0;
  i++;
  points[i].x = width + 1;
  points[i].y = 11.0;
  i++;
  points[i].x = width + 2;
  points[i].y = 15.0;
  i++;
  points[i].x = width + 3;
  points[i].y = 21.0;
  i++;
  points[i].x = width + 2;
  points[i].y = 21.0;
  i++;
  points[i].x = 0.0;
  points[i].y = 8.0;
  i++;

  createLathedSurface(points, NULL, i, i * 5, i * 10);
}
