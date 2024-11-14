#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
struct WeightIndex {
  double weight;
  int index;
};

struct ValueIndex {
  double value;
  int index;
};

class ParticleFilter {
private:
  std::mt19937 generator;
  std::normal_distribution<double> normal_dist;
  std::uniform_real_distribution<double> uniform_dist;

  double measurementNoiseStdev;
  double speedStdev;
  double speed;
  double planePosX;
  double planePosY;

  int FirstRun;

  int N;
  double m;
  double k;
  double plotHeight;

  double initial_weight;

  sf::RectangleShape plane;

  std::vector<double> y_coordinates;

  std::vector<double> w;

  std::vector<double> particles;

  void initFunctions();

public:
  ParticleFilter();
  void draw(sf::RenderWindow &window);
  bool compareValueIndex(const ValueIndex &a, const ValueIndex &b);
  double ground(double x);
  void normalizeWeights(std::vector<double> &w);
  std::vector<int> sortWeightsDescending(const std::vector<double> &w);
  void update();
};

#endif
