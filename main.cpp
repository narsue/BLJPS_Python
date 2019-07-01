#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include "BL_JPS.h"
#include <vector>

namespace py = pybind11;
using namespace pybind11::literals;

PYBIND11_MODULE(BL_JPS, m) {
	m.doc() = "Python bindings for the C++ implementation of BL_JPS";

	py::class_<BL_JPS>(m, "BL_JPS")
		.def(py::init<vector<int>, int, int>(), "Construct a pathfinder", "grid"_a, "width"_a, "height"_a)
		.def("flushReProcess", &BL_JPS::flushReProcess, "")
		.def("preProcessGrid", &BL_JPS::preProcessGrid, "")
		.def("findSolution", &BL_JPS::findSolution, "", "sX"_a, "sY"_a, "eX"_a, "eY"_a);

	py::class_<Coordinate>(m, "Coordinate")
		.def(py::init<>())
		.def(py::init<short, short>())
		.def("dist", &Coordinate::dist, "", "rhs"_a)
		.def("distSqrt", &Coordinate::distSqrt, "", "rhs"_a)
		.def("add", &Coordinate::add, "", "rhs"_a)
		.def_readwrite("x", &Coordinate::x)
		.def_readwrite("y", &Coordinate::y)
		.def("__getitem__", [](const Coordinate& c, size_t i) {
			if (i < 0 || i > 1) throw py::index_error("Index out of bounds");
			return c[i];
			})
		.def("__setitem__", [](Coordinate& c, size_t i, float v) {
				if (i < 0 || i > 1) throw py::index_error("Index out of bounds");
				c[i] = v;
			})
		.def("__eq__", &Coordinate::operator==, py::is_operator())
		.def("__neq__", &Coordinate::operator!=, py::is_operator());
}
