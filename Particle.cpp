#include "./Particle.h"

ParticleFilter::ParticleFilter()
    : generator(1), normal_dist(0.0, 1.0), uniform_dist(-40.0, 40.0),
      measurementNoiseStdev(0.1), speedStdev(1.0), speed(1.0), planePosX(-25.0),
      planePosY(4.0), FirstRun(1), N(200), m(1000), k(0.0001), plotHeight(5.0),
      initial_weight(1.0 / N), y_coordinates(N, plotHeight),
      w(N, initial_weight), particles(N)

{
  initFunctions();
  plane.setSize(sf::Vector2f(20, 20));
  plane.setFillColor(sf::Color::Red);
  plane.setPosition(sf::Vector2f(40, 60));
}

void ParticleFilter::initFunctions() {

  for (auto &p : particles) {
    p = uniform_dist(generator);
  }
}

bool ParticleFilter::compareValueIndex(const ValueIndex &a,
                                       const ValueIndex &b) {
  return a.value < b.value;
}

double ParticleFilter::ground(double x) {
  if (x >= 10) {
    return ((1 - (x - 10) / 30) * sin(x - 10) +
            ((x - 10) / 30) * sin(1.5 * (x - 10)) + 0.2 * (x - 10) * (x <= 20) +
            2 * (x > 20));
  } else if (x <= -10) {
    return ((1 - (-x - 10) / 30) * sin(-x - 10) +
            ((-x - 10) / 30) * sin(1.5 * (-x - 10)) +
            0.2 * (-x - 10) * (x >= -20) + 2 * (x < -20));
  } else {
    return 0;
  }
}

void ParticleFilter::normalizeWeights(std::vector<double> &w) {
  double sum_w = std::accumulate(w.begin(), w.end(), 0.0);

  if (sum_w > 0) {
    std::transform(w.begin(), w.end(), w.begin(),
                   [sum_w](double &weight) { return weight / sum_w; });
  } else {
    double uniform_weight = 1.0 / w.size();
    std::fill(w.begin(), w.end(), uniform_weight);
  }
}

std::vector<int>
ParticleFilter::sortWeightsDescending(const std::vector<double> &w) {
  std::vector<WeightIndex> weightIndexVector;
  for (int i = 0; i < w.size(); ++i) {
    weightIndexVector.push_back({w[i], i});
  }

  std::sort(weightIndexVector.begin(), weightIndexVector.end(),
            [](const WeightIndex &a, const WeightIndex &b) {
              return a.weight > b.weight;
            });

  std::vector<int> sortedIndices;
  for (const auto &weightIndex : weightIndexVector) {
    sortedIndices.push_back(weightIndex.index);
  }

  return sortedIndices;
}

void ParticleFilter::update() {

  double planeMeasDist = planePosY - ground(planePosX) +
                         normal_dist(generator) * measurementNoiseStdev;

  for (int i = 0; i < N; ++i) {
    double diff = planePosY - ground(particles[i]) - planeMeasDist;
    double weight = (1.0 / (sqrt(2 * M_PI) * measurementNoiseStdev)) *
                    exp(-0.5 * (diff * diff) /
                        (measurementNoiseStdev * measurementNoiseStdev));
    w[i] *= weight;
  }

  normalizeWeights(w);

  std::vector<double> wc(N);
  std::partial_sum(w.begin(), w.end(), wc.begin());

  std::vector<double> reorderedParticles(N);
  double step = 1.0 / N;
  double u = uniform_dist(generator) * step;
  int j = 0;

  for (int i = 0; i < N; ++i) {
    while (u > wc[j]) {
      j++;
    }
    reorderedParticles[i] = particles[j];
    u += step;
  }

  particles = reorderedParticles;
  std::fill(w.begin(), w.end(), initial_weight);

  for (int i = 0; i < N; ++i) {
    particles[i] += speed + normal_dist(generator) * speedStdev;
  }

  planePosX += speed;
  FirstRun = 0;

  std::cout << "Position X: " << planePosX << std::endl;
  std::cout << "Weight: " << w.size() << std::endl;
}

void ParticleFilter::draw(sf::RenderWindow &window) {

  sf::VertexArray groundVertices(sf::TriangleStrip);
  for (double x = -40.0; x <= 40.0; x += 0.1) {
    double y = ground(x) * 20 + 300;
    sf::Vertex vertex(
        sf::Vector2f(static_cast<float>(x * 10 + 400), static_cast<float>(y)));
    vertex.color = sf::Color::Green;
    groundVertices.append(vertex);
    groundVertices.append(sf::Vertex(
        sf::Vector2f(static_cast<float>(x * 10 + 400), 600), sf::Color::Blue));
  }

  window.draw(groundVertices);

  for (const auto &particle : particles) {
    sf::CircleShape shape(2.0f);
    shape.setPosition(static_cast<float>(particle * 10 + 400), 200.0f);
    shape.setFillColor(sf::Color::Red);
    window.draw(shape);
  }

  plane.setSize(sf::Vector2f(20, 20));
  plane.setFillColor(sf::Color::Red);
  plane.setPosition(static_cast<float>(planePosX * 10 + 400), 100.0f);
  window.draw(plane);
}
