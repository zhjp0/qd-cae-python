
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

// forward declarations
class Node;
class DB_Elements;

// includes
#include <dyna_cpp/utility/PythonUtility.hpp>

#include <memory>
#include <set>
#include <vector>

class Element
{
public:
  enum ElementType
  {
    NONE,
    BEAM,
    SHELL,
    SOLID
  };

private:
  int elementID;
  bool is_rigid;
  std::vector<size_t> nodes; // indexes
  std::vector<float> energy;
  std::vector<float> stress_mises;
  std::vector<float> plastic_strain;
  std::vector<std::vector<float>> strain;
  std::vector<std::vector<float>> stress;
  std::vector<std::vector<float>> history_vars;
  ElementType elemType;
  DB_Elements* db_elements;

public:
  Element(const int _id,
          const ElementType _etype,
          const std::vector<size_t>& _nodes,
          DB_Elements* db_elements);
  ~Element();
  bool operator<(const Element& other) const;
  void check() const;

  // getter
  ElementType get_elementType() const;
  int get_elementID() const;
  bool get_is_rigid() const;
  float get_estimated_element_size() const; // fast
  std::vector<std::shared_ptr<Node>> get_nodes() const;
  std::vector<int> get_node_ids() const;
  std::vector<size_t> get_node_indexes() const;
  std::vector<float> get_coords(int iTimestep = 0) const;
  std::vector<float> get_energy() const;
  std::vector<float> get_stress_mises() const;
  std::vector<float> get_plastic_strain() const;
  std::vector<std::vector<float>> get_strain() const;
  std::vector<std::vector<float>> get_stress() const;
  std::vector<std::vector<float>> get_history_vars() const;

  // setter
  void set_is_rigid(bool _is_rigid);
  void add_energy(float _energy);
  void add_stress_mises(float _stress_mises);
  void add_plastic_strain(float _plastic_strain);
  void add_stress(std::vector<float> _stress);
  void add_strain(std::vector<float> _strain);
  void add_history_vars(std::vector<float> vars, size_t iTimestep);

  // clear memory
  void clear_energy();
  void clear_plastic_strain();
  void clear_stress();
  void clear_stress_mises();
  void clear_strain();
  void clear_history_vars();

  // Python API
  pybind11::array_t<float> get_coords_py(int iTimestep = 0) const
  {
    return qd::py::vector_to_nparray(this->get_coords(iTimestep));
  };
  pybind11::array_t<float> get_energy_py() const
  {
    return qd::py::vector_to_nparray(this->get_energy());
  };
  pybind11::array_t<float> get_stress_mises_py() const
  {
    return qd::py::vector_to_nparray(this->get_stress_mises());
  };
  pybind11::array_t<float> get_plastic_strain_py() const
  {
    return qd::py::vector_to_nparray(this->get_plastic_strain());
  };
  pybind11::array_t<float> get_strain_py() const
  {
    return qd::py::vector_to_nparray(this->get_strain());
  };
  pybind11::array_t<float> get_stress_py() const
  {
    return qd::py::vector_to_nparray(this->get_stress());
  };
  pybind11::array_t<float> get_history_vars_py() const
  {
    return qd::py::vector_to_nparray(this->get_history_vars());
  };
};

#endif
