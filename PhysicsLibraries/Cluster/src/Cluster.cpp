#include "Cluster.h"
#include "cinder/Rand.h"
#include "VerletParticle.h"
#include "VerletSpring.h"
#include "cinder/gl/gl.h"

using namespace ci;

Cluster::Cluster(VerletPhysics * physics, int n, float d, ci::Vec2f center) {

  diameter = d;
  for (int i = 0; i < n; i++) {
    nodes.push_back(new Node(center + ci::Rand::randVec2f()));
  }

  for (int i = 0; i < n - 1; i++) {
    VerletParticle * ni = nodes.at(i);
    for (int j = i+1; j < n; j++) {
      VerletParticle * nj = nodes.at(j);
      physics->addSpring(new VerletSpring(ni, nj, diameter, 0.1));
    }
  }
}

void Cluster::draw() {
  int n = (int)nodes.size();
  for (int i = 0; i < n; i++) {
    nodes.at(i)->draw();
  }
  
  ci::gl::color(0.8, 0.8, 0.8, 1);
  for (int i = 0; i < n - 1; i++) {
    VerletParticle * ni = nodes.at(i);
    for (int j = i+1; j < n; j++) {
      VerletParticle * nj = nodes.at(j);
      gl::drawLine(ni->position, nj->position);
    }
  }
}
