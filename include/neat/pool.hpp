#pragma once

#include <cstdint>
#include <unordered_map>
#include "species.hpp"
#include "serial.hpp"

#define stale_species 15
#define population 300

using std::int32_t;
using std::vector;

struct Pool : public Serial {
public:
  static int32_t innovate();
  static int32_t innovation; // Serves as a counter

  Pool(int32_t inputs_, int32_t outputs_);
  Pool(const Pool &other);
  Pool(Pool &&other);
  Pool &operator=(Pool other);
  virtual ~Pool() {}

  vector<bool> evaluate(const vector<int32_t> &inputs);

  bool save(ofstream &ofs) const;
  bool load(ifstream &ifs);

  void set_top();
  void next_genome();
  bool fitness_measured() const;
  void generate_top_network();

  Genome &top_genome();
  void reset_frame();
  void advance_frame();
  int32_t get_frame();
  void update_fitness(int32_t new_fitness);

private:
  vector<Species> species;
  int32_t generation;
  int32_t current_species;
  int32_t current_genome;
  int32_t current_frame;
  int32_t max_fitness;
  int32_t inputs, outputs;

  void rank_globally();
  int32_t calculate_average_fitness();
  void cull_species(bool cut_to_one);
  void remove_stale_species();
  void remove_weak_species();
  void add_to_species(Genome child);
  void new_generation();

  void copy(const Pool &other);
  void swap(Pool &other);
};
