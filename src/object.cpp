#include <cmath>

#include "object.hpp"

inline const std::tuple<int, int, int> triangle_pos[][256] = {
    {},
    { std::make_tuple(0, 8, 3) },
    { std::make_tuple(0, 1, 9) },
    { std::make_tuple(1, 8, 3), std::make_tuple(9, 8, 1) },
    { std::make_tuple(1, 2, 10) },
    { std::make_tuple(0, 8, 3), std::make_tuple(1, 2, 10) },
    { std::make_tuple(9, 2, 10), std::make_tuple(0, 2, 9) },
    { std::make_tuple(2, 8, 3), std::make_tuple(2, 10, 8),
      std::make_tuple(10, 9, 8) },
    { std::make_tuple(3, 11, 2) },
    { std::make_tuple(0, 11, 2), std::make_tuple(8, 11, 0) },
    { std::make_tuple(1, 9, 0), std::make_tuple(2, 3, 11) },
    { std::make_tuple(1, 11, 2), std::make_tuple(1, 9, 11),
      std::make_tuple(9, 8, 11) },
    { std::make_tuple(3, 10, 1), std::make_tuple(11, 10, 3) },
    { std::make_tuple(0, 10, 1), std::make_tuple(0, 8, 10),
      std::make_tuple(8, 11, 10) },
    { std::make_tuple(3, 9, 0), std::make_tuple(3, 11, 9),
      std::make_tuple(11, 10, 9) },
    { std::make_tuple(9, 8, 10), std::make_tuple(10, 8, 11) },
    { std::make_tuple(4, 7, 8) },
    { std::make_tuple(4, 3, 0), std::make_tuple(7, 3, 4) },
    { std::make_tuple(0, 1, 9), std::make_tuple(8, 4, 7) },
    { std::make_tuple(4, 1, 9), std::make_tuple(4, 7, 1),
      std::make_tuple(7, 3, 1) },
    { std::make_tuple(1, 2, 10), std::make_tuple(8, 4, 7) },
    { std::make_tuple(3, 4, 7), std::make_tuple(3, 0, 4),
      std::make_tuple(1, 2, 10) },
    { std::make_tuple(9, 2, 10), std::make_tuple(9, 0, 2),
      std::make_tuple(8, 4, 7) },
    { std::make_tuple(2, 10, 9), std::make_tuple(2, 9, 7),
      std::make_tuple(2, 7, 3), std::make_tuple(7, 9, 4) },
    { std::make_tuple(8, 4, 7), std::make_tuple(3, 11, 2) },
    { std::make_tuple(11, 4, 7), std::make_tuple(11, 2, 4),
      std::make_tuple(2, 0, 4) },
    { std::make_tuple(9, 0, 1), std::make_tuple(8, 4, 7),
      std::make_tuple(2, 3, 11) },
    { std::make_tuple(4, 7, 11), std::make_tuple(9, 4, 11),
      std::make_tuple(9, 11, 2), std::make_tuple(9, 2, 1) },
    { std::make_tuple(3, 10, 1), std::make_tuple(3, 11, 10),
      std::make_tuple(7, 8, 4) },
    { std::make_tuple(1, 11, 10), std::make_tuple(1, 4, 11),
      std::make_tuple(1, 0, 4), std::make_tuple(7, 11, 4) },
    { std::make_tuple(4, 7, 8), std::make_tuple(9, 0, 11),
      std::make_tuple(9, 11, 10), std::make_tuple(11, 0, 3) },
    { std::make_tuple(4, 7, 11), std::make_tuple(4, 11, 9),
      std::make_tuple(9, 11, 10) },
    { std::make_tuple(9, 5, 4) },
    { std::make_tuple(9, 5, 4), std::make_tuple(0, 8, 3) },
    { std::make_tuple(0, 5, 4), std::make_tuple(1, 5, 0) },
    { std::make_tuple(8, 5, 4), std::make_tuple(8, 3, 5),
      std::make_tuple(3, 1, 5) },
    { std::make_tuple(1, 2, 10), std::make_tuple(9, 5, 4) },
    { std::make_tuple(3, 0, 8), std::make_tuple(1, 2, 10),
      std::make_tuple(4, 9, 5) },
    { std::make_tuple(5, 2, 10), std::make_tuple(5, 4, 2),
      std::make_tuple(4, 0, 2) },
    { std::make_tuple(2, 10, 5), std::make_tuple(3, 2, 5),
      std::make_tuple(3, 5, 4), std::make_tuple(3, 4, 8) },
    { std::make_tuple(9, 5, 4), std::make_tuple(2, 3, 11) },
    { std::make_tuple(0, 11, 2), std::make_tuple(0, 8, 11),
      std::make_tuple(4, 9, 5) },
    { std::make_tuple(0, 5, 4), std::make_tuple(0, 1, 5),
      std::make_tuple(2, 3, 11) },
    { std::make_tuple(2, 1, 5), std::make_tuple(2, 5, 8),
      std::make_tuple(2, 8, 11), std::make_tuple(4, 8, 5) },
    { std::make_tuple(10, 3, 11), std::make_tuple(10, 1, 3),
      std::make_tuple(9, 5, 4) },
    { std::make_tuple(4, 9, 5), std::make_tuple(0, 8, 1),
      std::make_tuple(8, 10, 1), std::make_tuple(8, 11, 10) },
    { std::make_tuple(5, 4, 0), std::make_tuple(5, 0, 11),
      std::make_tuple(5, 11, 10), std::make_tuple(11, 0, 3) },
    { std::make_tuple(5, 4, 8), std::make_tuple(5, 8, 10),
      std::make_tuple(10, 8, 11) },
    { std::make_tuple(9, 7, 8), std::make_tuple(5, 7, 9) },
    { std::make_tuple(9, 3, 0), std::make_tuple(9, 5, 3),
      std::make_tuple(5, 7, 3) },
    { std::make_tuple(0, 7, 8), std::make_tuple(0, 1, 7),
      std::make_tuple(1, 5, 7) },
    { std::make_tuple(1, 5, 3), std::make_tuple(3, 5, 7) },
    { std::make_tuple(9, 7, 8), std::make_tuple(9, 5, 7),
      std::make_tuple(10, 1, 2) },
    { std::make_tuple(10, 1, 2), std::make_tuple(9, 5, 0),
      std::make_tuple(5, 3, 0), std::make_tuple(5, 7, 3) },
    { std::make_tuple(8, 0, 2), std::make_tuple(8, 2, 5),
      std::make_tuple(8, 5, 7), std::make_tuple(10, 5, 2) },
    { std::make_tuple(2, 10, 5), std::make_tuple(2, 5, 3),
      std::make_tuple(3, 5, 7) },
    { std::make_tuple(7, 9, 5), std::make_tuple(7, 8, 9),
      std::make_tuple(3, 11, 2) },
    { std::make_tuple(9, 5, 7), std::make_tuple(9, 7, 2),
      std::make_tuple(9, 2, 0), std::make_tuple(2, 7, 11) },
    { std::make_tuple(2, 3, 11), std::make_tuple(0, 1, 8),
      std::make_tuple(1, 7, 8), std::make_tuple(1, 5, 7) },
    { std::make_tuple(11, 2, 1), std::make_tuple(11, 1, 7),
      std::make_tuple(7, 1, 5) },
    { std::make_tuple(9, 5, 8), std::make_tuple(8, 5, 7),
      std::make_tuple(10, 1, 3), std::make_tuple(10, 3, 11) },
    { std::make_tuple(5, 7, 0), std::make_tuple(5, 0, 9),
      std::make_tuple(7, 11, 0), std::make_tuple(1, 0, 10),
      std::make_tuple(11, 10, 0) },
    { std::make_tuple(11, 10, 0), std::make_tuple(11, 0, 3),
      std::make_tuple(10, 5, 0), std::make_tuple(8, 0, 7),
      std::make_tuple(5, 7, 0) },
    { std::make_tuple(11, 10, 5), std::make_tuple(7, 11, 5) },
    { std::make_tuple(10, 6, 5) },
    { std::make_tuple(0, 8, 3), std::make_tuple(5, 10, 6) },
    { std::make_tuple(9, 0, 1), std::make_tuple(5, 10, 6) },
    { std::make_tuple(1, 8, 3), std::make_tuple(1, 9, 8),
      std::make_tuple(5, 10, 6) },
    { std::make_tuple(1, 6, 5), std::make_tuple(2, 6, 1) },
    { std::make_tuple(1, 6, 5), std::make_tuple(1, 2, 6),
      std::make_tuple(3, 0, 8) },
    { std::make_tuple(9, 6, 5), std::make_tuple(9, 0, 6),
      std::make_tuple(0, 2, 6) },
    { std::make_tuple(5, 9, 8), std::make_tuple(5, 8, 2),
      std::make_tuple(5, 2, 6), std::make_tuple(3, 2, 8) },
    { std::make_tuple(2, 3, 11), std::make_tuple(10, 6, 5) },
    { std::make_tuple(11, 0, 8), std::make_tuple(11, 2, 0),
      std::make_tuple(10, 6, 5) },
    { std::make_tuple(0, 1, 9), std::make_tuple(2, 3, 11),
      std::make_tuple(5, 10, 6) },
    { std::make_tuple(5, 10, 6), std::make_tuple(1, 9, 2),
      std::make_tuple(9, 11, 2), std::make_tuple(9, 8, 11) },
    { std::make_tuple(6, 3, 11), std::make_tuple(6, 5, 3),
      std::make_tuple(5, 1, 3) },
    { std::make_tuple(0, 8, 11), std::make_tuple(0, 11, 5),
      std::make_tuple(0, 5, 1), std::make_tuple(5, 11, 6) },
    { std::make_tuple(3, 11, 6), std::make_tuple(0, 3, 6),
      std::make_tuple(0, 6, 5), std::make_tuple(0, 5, 9) },
    { std::make_tuple(6, 5, 9), std::make_tuple(6, 9, 11),
      std::make_tuple(11, 9, 8) },
    { std::make_tuple(5, 10, 6), std::make_tuple(4, 7, 8) },
    { std::make_tuple(4, 3, 0), std::make_tuple(4, 7, 3),
      std::make_tuple(6, 5, 10) },
    { std::make_tuple(1, 9, 0), std::make_tuple(5, 10, 6),
      std::make_tuple(8, 4, 7) },
    { std::make_tuple(10, 6, 5), std::make_tuple(1, 9, 7),
      std::make_tuple(1, 7, 3), std::make_tuple(7, 9, 4) },
    { std::make_tuple(6, 1, 2), std::make_tuple(6, 5, 1),
      std::make_tuple(4, 7, 8) },
    { std::make_tuple(1, 2, 5), std::make_tuple(5, 2, 6),
      std::make_tuple(3, 0, 4), std::make_tuple(3, 4, 7) },
    { std::make_tuple(8, 4, 7), std::make_tuple(9, 0, 5),
      std::make_tuple(0, 6, 5), std::make_tuple(0, 2, 6) },
    { std::make_tuple(7, 3, 9), std::make_tuple(7, 9, 4),
      std::make_tuple(3, 2, 9), std::make_tuple(5, 9, 6),
      std::make_tuple(2, 6, 9) },
    { std::make_tuple(3, 11, 2), std::make_tuple(7, 8, 4),
      std::make_tuple(10, 6, 5) },
    { std::make_tuple(5, 10, 6), std::make_tuple(4, 7, 2),
      std::make_tuple(4, 2, 0), std::make_tuple(2, 7, 11) },
    { std::make_tuple(0, 1, 9), std::make_tuple(4, 7, 8),
      std::make_tuple(2, 3, 11), std::make_tuple(5, 10, 6) },
    { std::make_tuple(9, 2, 1), std::make_tuple(9, 11, 2),
      std::make_tuple(9, 4, 11), std::make_tuple(7, 11, 4),
      std::make_tuple(5, 10, 6) },
    { std::make_tuple(8, 4, 7), std::make_tuple(3, 11, 5),
      std::make_tuple(3, 5, 1), std::make_tuple(5, 11, 6) },
    { std::make_tuple(5, 1, 11), std::make_tuple(5, 11, 6),
      std::make_tuple(1, 0, 11), std::make_tuple(7, 11, 4),
      std::make_tuple(0, 4, 11) },
    { std::make_tuple(0, 5, 9), std::make_tuple(0, 6, 5),
      std::make_tuple(0, 3, 6), std::make_tuple(11, 6, 3),
      std::make_tuple(8, 4, 7) },
    { std::make_tuple(6, 5, 9), std::make_tuple(6, 9, 11),
      std::make_tuple(4, 7, 9), std::make_tuple(7, 11, 9) },
    { std::make_tuple(10, 4, 9), std::make_tuple(6, 4, 10) },
    { std::make_tuple(4, 10, 6), std::make_tuple(4, 9, 10),
      std::make_tuple(0, 8, 3) },
    { std::make_tuple(10, 0, 1), std::make_tuple(10, 6, 0),
      std::make_tuple(6, 4, 0) },
    { std::make_tuple(8, 3, 1), std::make_tuple(8, 1, 6),
      std::make_tuple(8, 6, 4), std::make_tuple(6, 1, 10) },
    { std::make_tuple(1, 4, 9), std::make_tuple(1, 2, 4),
      std::make_tuple(2, 6, 4) },
    { std::make_tuple(3, 0, 8), std::make_tuple(1, 2, 9),
      std::make_tuple(2, 4, 9), std::make_tuple(2, 6, 4) },
    { std::make_tuple(0, 2, 4), std::make_tuple(4, 2, 6) },
    { std::make_tuple(8, 3, 2), std::make_tuple(8, 2, 4),
      std::make_tuple(4, 2, 6) },
    { std::make_tuple(10, 4, 9), std::make_tuple(10, 6, 4),
      std::make_tuple(11, 2, 3) },
    { std::make_tuple(0, 8, 2), std::make_tuple(2, 8, 11),
      std::make_tuple(4, 9, 10), std::make_tuple(4, 10, 6) },
    { std::make_tuple(3, 11, 2), std::make_tuple(0, 1, 6),
      std::make_tuple(0, 6, 4), std::make_tuple(6, 1, 10) },
    { std::make_tuple(6, 4, 1), std::make_tuple(6, 1, 10),
      std::make_tuple(4, 8, 1), std::make_tuple(2, 1, 11),
      std::make_tuple(8, 11, 1) },
    { std::make_tuple(9, 6, 4), std::make_tuple(9, 3, 6),
      std::make_tuple(9, 1, 3), std::make_tuple(11, 6, 3) },
    { std::make_tuple(8, 11, 1), std::make_tuple(8, 1, 0),
      std::make_tuple(11, 6, 1), std::make_tuple(9, 1, 4),
      std::make_tuple(6, 4, 1) },
    { std::make_tuple(3, 11, 6), std::make_tuple(3, 6, 0),
      std::make_tuple(0, 6, 4) },
    { std::make_tuple(6, 4, 8), std::make_tuple(11, 6, 8) },
    { std::make_tuple(7, 10, 6), std::make_tuple(7, 8, 10),
      std::make_tuple(8, 9, 10) },
    { std::make_tuple(0, 7, 3), std::make_tuple(0, 10, 7),
      std::make_tuple(0, 9, 10), std::make_tuple(6, 7, 10) },
    { std::make_tuple(10, 6, 7), std::make_tuple(1, 10, 7),
      std::make_tuple(1, 7, 8), std::make_tuple(1, 8, 0) },
    { std::make_tuple(10, 6, 7), std::make_tuple(10, 7, 1),
      std::make_tuple(1, 7, 3) },
    { std::make_tuple(1, 2, 6), std::make_tuple(1, 6, 8),
      std::make_tuple(1, 8, 9), std::make_tuple(8, 6, 7) },
    { std::make_tuple(2, 6, 9), std::make_tuple(2, 9, 1),
      std::make_tuple(6, 7, 9), std::make_tuple(0, 9, 3),
      std::make_tuple(7, 3, 9) },
    { std::make_tuple(7, 8, 0), std::make_tuple(7, 0, 6),
      std::make_tuple(6, 0, 2) },
    { std::make_tuple(7, 3, 2), std::make_tuple(6, 7, 2) },
    { std::make_tuple(2, 3, 11), std::make_tuple(10, 6, 8),
      std::make_tuple(10, 8, 9), std::make_tuple(8, 6, 7) },
    { std::make_tuple(2, 0, 7), std::make_tuple(2, 7, 11),
      std::make_tuple(0, 9, 7), std::make_tuple(6, 7, 10),
      std::make_tuple(9, 10, 7) },
    { std::make_tuple(1, 8, 0), std::make_tuple(1, 7, 8),
      std::make_tuple(1, 10, 7), std::make_tuple(6, 7, 10),
      std::make_tuple(2, 3, 11) },
    { std::make_tuple(11, 2, 1), std::make_tuple(11, 1, 7),
      std::make_tuple(10, 6, 1), std::make_tuple(6, 7, 1) },
    { std::make_tuple(8, 9, 6), std::make_tuple(8, 6, 7),
      std::make_tuple(9, 1, 6), std::make_tuple(11, 6, 3),
      std::make_tuple(1, 3, 6) },
    { std::make_tuple(0, 9, 1), std::make_tuple(11, 6, 7) },
    { std::make_tuple(7, 8, 0), std::make_tuple(7, 0, 6),
      std::make_tuple(3, 11, 0), std::make_tuple(11, 6, 0) },
    { std::make_tuple(7, 11, 6) },
    { std::make_tuple(7, 6, 11) },
    { std::make_tuple(3, 0, 8), std::make_tuple(11, 7, 6) },
    { std::make_tuple(0, 1, 9), std::make_tuple(11, 7, 6) },
    { std::make_tuple(8, 1, 9), std::make_tuple(8, 3, 1),
      std::make_tuple(11, 7, 6) },
    { std::make_tuple(10, 1, 2), std::make_tuple(6, 11, 7) },
    { std::make_tuple(1, 2, 10), std::make_tuple(3, 0, 8),
      std::make_tuple(6, 11, 7) },
    { std::make_tuple(2, 9, 0), std::make_tuple(2, 10, 9),
      std::make_tuple(6, 11, 7) },
    { std::make_tuple(6, 11, 7), std::make_tuple(2, 10, 3),
      std::make_tuple(10, 8, 3), std::make_tuple(10, 9, 8) },
    { std::make_tuple(7, 2, 3), std::make_tuple(6, 2, 7) },
    { std::make_tuple(7, 0, 8), std::make_tuple(7, 6, 0),
      std::make_tuple(6, 2, 0) },
    { std::make_tuple(2, 7, 6), std::make_tuple(2, 3, 7),
      std::make_tuple(0, 1, 9) },
    { std::make_tuple(1, 6, 2), std::make_tuple(1, 8, 6),
      std::make_tuple(1, 9, 8), std::make_tuple(8, 7, 6) },
    { std::make_tuple(10, 7, 6), std::make_tuple(10, 1, 7),
      std::make_tuple(1, 3, 7) },
    { std::make_tuple(10, 7, 6), std::make_tuple(1, 7, 10),
      std::make_tuple(1, 8, 7), std::make_tuple(1, 0, 8) },
    { std::make_tuple(0, 3, 7), std::make_tuple(0, 7, 10),
      std::make_tuple(0, 10, 9), std::make_tuple(6, 10, 7) },
    { std::make_tuple(7, 6, 10), std::make_tuple(7, 10, 8),
      std::make_tuple(8, 10, 9) },
    { std::make_tuple(6, 8, 4), std::make_tuple(11, 8, 6) },
    { std::make_tuple(3, 6, 11), std::make_tuple(3, 0, 6),
      std::make_tuple(0, 4, 6) },
    { std::make_tuple(8, 6, 11), std::make_tuple(8, 4, 6),
      std::make_tuple(9, 0, 1) },
    { std::make_tuple(9, 4, 6), std::make_tuple(9, 6, 3),
      std::make_tuple(9, 3, 1), std::make_tuple(11, 3, 6) },
    { std::make_tuple(6, 8, 4), std::make_tuple(6, 11, 8),
      std::make_tuple(2, 10, 1) },
    { std::make_tuple(1, 2, 10), std::make_tuple(3, 0, 11),
      std::make_tuple(0, 6, 11), std::make_tuple(0, 4, 6) },
    { std::make_tuple(4, 11, 8), std::make_tuple(4, 6, 11),
      std::make_tuple(0, 2, 9), std::make_tuple(2, 10, 9) },
    { std::make_tuple(10, 9, 3), std::make_tuple(10, 3, 2),
      std::make_tuple(9, 4, 3), std::make_tuple(11, 3, 6),
      std::make_tuple(4, 6, 3) },
    { std::make_tuple(8, 2, 3), std::make_tuple(8, 4, 2),
      std::make_tuple(4, 6, 2) },
    { std::make_tuple(0, 4, 2), std::make_tuple(4, 6, 2) },
    { std::make_tuple(1, 9, 0), std::make_tuple(2, 3, 4),
      std::make_tuple(2, 4, 6), std::make_tuple(4, 3, 8) },
    { std::make_tuple(1, 9, 4), std::make_tuple(1, 4, 2),
      std::make_tuple(2, 4, 6) },
    { std::make_tuple(8, 1, 3), std::make_tuple(8, 6, 1),
      std::make_tuple(8, 4, 6), std::make_tuple(6, 10, 1) },
    { std::make_tuple(10, 1, 0), std::make_tuple(10, 0, 6),
      std::make_tuple(6, 0, 4) },
    { std::make_tuple(4, 6, 3), std::make_tuple(4, 3, 8),
      std::make_tuple(6, 10, 3), std::make_tuple(0, 3, 9),
      std::make_tuple(10, 9, 3) },
    { std::make_tuple(10, 9, 4), std::make_tuple(6, 10, 4) },
    { std::make_tuple(4, 9, 5), std::make_tuple(7, 6, 11) },
    { std::make_tuple(0, 8, 3), std::make_tuple(4, 9, 5),
      std::make_tuple(11, 7, 6) },
    { std::make_tuple(5, 0, 1), std::make_tuple(5, 4, 0),
      std::make_tuple(7, 6, 11) },
    { std::make_tuple(11, 7, 6), std::make_tuple(8, 3, 4),
      std::make_tuple(3, 5, 4), std::make_tuple(3, 1, 5) },
    { std::make_tuple(9, 5, 4), std::make_tuple(10, 1, 2),
      std::make_tuple(7, 6, 11) },
    { std::make_tuple(6, 11, 7), std::make_tuple(1, 2, 10),
      std::make_tuple(0, 8, 3), std::make_tuple(4, 9, 5) },
    { std::make_tuple(7, 6, 11), std::make_tuple(5, 4, 10),
      std::make_tuple(4, 2, 10), std::make_tuple(4, 0, 2) },
    { std::make_tuple(3, 4, 8), std::make_tuple(3, 5, 4),
      std::make_tuple(3, 2, 5), std::make_tuple(10, 5, 2),
      std::make_tuple(11, 7, 6) },
    { std::make_tuple(7, 2, 3), std::make_tuple(7, 6, 2),
      std::make_tuple(5, 4, 9) },
    { std::make_tuple(9, 5, 4), std::make_tuple(0, 8, 6),
      std::make_tuple(0, 6, 2), std::make_tuple(6, 8, 7) },
    { std::make_tuple(3, 6, 2), std::make_tuple(3, 7, 6),
      std::make_tuple(1, 5, 0), std::make_tuple(5, 4, 0) },
    { std::make_tuple(6, 2, 8), std::make_tuple(6, 8, 7),
      std::make_tuple(2, 1, 8), std::make_tuple(4, 8, 5),
      std::make_tuple(1, 5, 8) },
    { std::make_tuple(9, 5, 4), std::make_tuple(10, 1, 6),
      std::make_tuple(1, 7, 6), std::make_tuple(1, 3, 7) },
    { std::make_tuple(1, 6, 10), std::make_tuple(1, 7, 6),
      std::make_tuple(1, 0, 7), std::make_tuple(8, 7, 0),
      std::make_tuple(9, 5, 4) },
    { std::make_tuple(4, 0, 10), std::make_tuple(4, 10, 5),
      std::make_tuple(0, 3, 10), std::make_tuple(6, 10, 7),
      std::make_tuple(3, 7, 10) },
    { std::make_tuple(7, 6, 10), std::make_tuple(7, 10, 8),
      std::make_tuple(5, 4, 10), std::make_tuple(4, 8, 10) },
    { std::make_tuple(6, 9, 5), std::make_tuple(6, 11, 9),
      std::make_tuple(11, 8, 9) },
    { std::make_tuple(3, 6, 11), std::make_tuple(0, 6, 3),
      std::make_tuple(0, 5, 6), std::make_tuple(0, 9, 5) },
    { std::make_tuple(0, 11, 8), std::make_tuple(0, 5, 11),
      std::make_tuple(0, 1, 5), std::make_tuple(5, 6, 11) },
    { std::make_tuple(6, 11, 3), std::make_tuple(6, 3, 5),
      std::make_tuple(5, 3, 1) },
    { std::make_tuple(1, 2, 10), std::make_tuple(9, 5, 11),
      std::make_tuple(9, 11, 8), std::make_tuple(11, 5, 6) },
    { std::make_tuple(0, 11, 3), std::make_tuple(0, 6, 11),
      std::make_tuple(0, 9, 6), std::make_tuple(5, 6, 9),
      std::make_tuple(1, 2, 10) },
    { std::make_tuple(11, 8, 5), std::make_tuple(11, 5, 6),
      std::make_tuple(8, 0, 5), std::make_tuple(10, 5, 2),
      std::make_tuple(0, 2, 5) },
    { std::make_tuple(6, 11, 3), std::make_tuple(6, 3, 5),
      std::make_tuple(2, 10, 3), std::make_tuple(10, 5, 3) },
    { std::make_tuple(5, 8, 9), std::make_tuple(5, 2, 8),
      std::make_tuple(5, 6, 2), std::make_tuple(3, 8, 2) },
    { std::make_tuple(9, 5, 6), std::make_tuple(9, 6, 0),
      std::make_tuple(0, 6, 2) },
    { std::make_tuple(1, 5, 8), std::make_tuple(1, 8, 0),
      std::make_tuple(5, 6, 8), std::make_tuple(3, 8, 2),
      std::make_tuple(6, 2, 8) },
    { std::make_tuple(1, 5, 6), std::make_tuple(2, 1, 6) },
    { std::make_tuple(1, 3, 6), std::make_tuple(1, 6, 10),
      std::make_tuple(3, 8, 6), std::make_tuple(5, 6, 9),
      std::make_tuple(8, 9, 6) },
    { std::make_tuple(10, 1, 0), std::make_tuple(10, 0, 6),
      std::make_tuple(9, 5, 0), std::make_tuple(5, 6, 0) },
    { std::make_tuple(0, 3, 8), std::make_tuple(5, 6, 10) },
    { std::make_tuple(10, 5, 6) },
    { std::make_tuple(11, 5, 10), std::make_tuple(7, 5, 11) },
    { std::make_tuple(11, 5, 10), std::make_tuple(11, 7, 5),
      std::make_tuple(8, 3, 0) },
    { std::make_tuple(5, 11, 7), std::make_tuple(5, 10, 11),
      std::make_tuple(1, 9, 0) },
    { std::make_tuple(10, 7, 5), std::make_tuple(10, 11, 7),
      std::make_tuple(9, 8, 1), std::make_tuple(8, 3, 1) },
    { std::make_tuple(11, 1, 2), std::make_tuple(11, 7, 1),
      std::make_tuple(7, 5, 1) },
    { std::make_tuple(0, 8, 3), std::make_tuple(1, 2, 7),
      std::make_tuple(1, 7, 5), std::make_tuple(7, 2, 11) },
    { std::make_tuple(9, 7, 5), std::make_tuple(9, 2, 7),
      std::make_tuple(9, 0, 2), std::make_tuple(2, 11, 7) },
    { std::make_tuple(7, 5, 2), std::make_tuple(7, 2, 11),
      std::make_tuple(5, 9, 2), std::make_tuple(3, 2, 8),
      std::make_tuple(9, 8, 2) },
    { std::make_tuple(2, 5, 10), std::make_tuple(2, 3, 5),
      std::make_tuple(3, 7, 5) },
    { std::make_tuple(8, 2, 0), std::make_tuple(8, 5, 2),
      std::make_tuple(8, 7, 5), std::make_tuple(10, 2, 5) },
    { std::make_tuple(9, 0, 1), std::make_tuple(5, 10, 3),
      std::make_tuple(5, 3, 7), std::make_tuple(3, 10, 2) },
    { std::make_tuple(9, 8, 2), std::make_tuple(9, 2, 1),
      std::make_tuple(8, 7, 2), std::make_tuple(10, 2, 5),
      std::make_tuple(7, 5, 2) },
    { std::make_tuple(1, 3, 5), std::make_tuple(3, 7, 5) },
    { std::make_tuple(0, 8, 7), std::make_tuple(0, 7, 1),
      std::make_tuple(1, 7, 5) },
    { std::make_tuple(9, 0, 3), std::make_tuple(9, 3, 5),
      std::make_tuple(5, 3, 7) },
    { std::make_tuple(9, 8, 7), std::make_tuple(5, 9, 7) },
    { std::make_tuple(5, 8, 4), std::make_tuple(5, 10, 8),
      std::make_tuple(10, 11, 8) },
    { std::make_tuple(5, 0, 4), std::make_tuple(5, 11, 0),
      std::make_tuple(5, 10, 11), std::make_tuple(11, 3, 0) },
    { std::make_tuple(0, 1, 9), std::make_tuple(8, 4, 10),
      std::make_tuple(8, 10, 11), std::make_tuple(10, 4, 5) },
    { std::make_tuple(10, 11, 4), std::make_tuple(10, 4, 5),
      std::make_tuple(11, 3, 4), std::make_tuple(9, 4, 1),
      std::make_tuple(3, 1, 4) },
    { std::make_tuple(2, 5, 1), std::make_tuple(2, 8, 5),
      std::make_tuple(2, 11, 8), std::make_tuple(4, 5, 8) },
    { std::make_tuple(0, 4, 11), std::make_tuple(0, 11, 3),
      std::make_tuple(4, 5, 11), std::make_tuple(2, 11, 1),
      std::make_tuple(5, 1, 11) },
    { std::make_tuple(0, 2, 5), std::make_tuple(0, 5, 9),
      std::make_tuple(2, 11, 5), std::make_tuple(4, 5, 8),
      std::make_tuple(11, 8, 5) },
    { std::make_tuple(9, 4, 5), std::make_tuple(2, 11, 3) },
    { std::make_tuple(2, 5, 10), std::make_tuple(3, 5, 2),
      std::make_tuple(3, 4, 5), std::make_tuple(3, 8, 4) },
    { std::make_tuple(5, 10, 2), std::make_tuple(5, 2, 4),
      std::make_tuple(4, 2, 0) },
    { std::make_tuple(3, 10, 2), std::make_tuple(3, 5, 10),
      std::make_tuple(3, 8, 5), std::make_tuple(4, 5, 8),
      std::make_tuple(0, 1, 9) },
    { std::make_tuple(5, 10, 2), std::make_tuple(5, 2, 4),
      std::make_tuple(1, 9, 2), std::make_tuple(9, 4, 2) },
    { std::make_tuple(8, 4, 5), std::make_tuple(8, 5, 3),
      std::make_tuple(3, 5, 1) },
    { std::make_tuple(0, 4, 5), std::make_tuple(1, 0, 5) },
    { std::make_tuple(8, 4, 5), std::make_tuple(8, 5, 3),
      std::make_tuple(9, 0, 5), std::make_tuple(0, 3, 5) },
    { std::make_tuple(9, 4, 5) },
    { std::make_tuple(4, 11, 7), std::make_tuple(4, 9, 11),
      std::make_tuple(9, 10, 11) },
    { std::make_tuple(0, 8, 3), std::make_tuple(4, 9, 7),
      std::make_tuple(9, 11, 7), std::make_tuple(9, 10, 11) },
    { std::make_tuple(1, 10, 11), std::make_tuple(1, 11, 4),
      std::make_tuple(1, 4, 0), std::make_tuple(7, 4, 11) },
    { std::make_tuple(3, 1, 4), std::make_tuple(3, 4, 8),
      std::make_tuple(1, 10, 4), std::make_tuple(7, 4, 11),
      std::make_tuple(10, 11, 4) },
    { std::make_tuple(4, 11, 7), std::make_tuple(9, 11, 4),
      std::make_tuple(9, 2, 11), std::make_tuple(9, 1, 2) },
    { std::make_tuple(9, 7, 4), std::make_tuple(9, 11, 7),
      std::make_tuple(9, 1, 11), std::make_tuple(2, 11, 1),
      std::make_tuple(0, 8, 3) },
    { std::make_tuple(11, 7, 4), std::make_tuple(11, 4, 2),
      std::make_tuple(2, 4, 0) },
    { std::make_tuple(11, 7, 4), std::make_tuple(11, 4, 2),
      std::make_tuple(8, 3, 4), std::make_tuple(3, 2, 4) },
    { std::make_tuple(2, 9, 10), std::make_tuple(2, 7, 9),
      std::make_tuple(2, 3, 7), std::make_tuple(7, 4, 9) },
    { std::make_tuple(9, 10, 7), std::make_tuple(9, 7, 4),
      std::make_tuple(10, 2, 7), std::make_tuple(8, 7, 0),
      std::make_tuple(2, 0, 7) },
    { std::make_tuple(3, 7, 10), std::make_tuple(3, 10, 2),
      std::make_tuple(7, 4, 10), std::make_tuple(1, 10, 0),
      std::make_tuple(4, 0, 10) },
    { std::make_tuple(1, 10, 2), std::make_tuple(8, 7, 4) },
    { std::make_tuple(4, 9, 1), std::make_tuple(4, 1, 7),
      std::make_tuple(7, 1, 3) },
    { std::make_tuple(4, 9, 1), std::make_tuple(4, 1, 7),
      std::make_tuple(0, 8, 1), std::make_tuple(8, 7, 1) },
    { std::make_tuple(4, 0, 3), std::make_tuple(7, 4, 3) },
    { std::make_tuple(4, 8, 7) },
    { std::make_tuple(9, 10, 8), std::make_tuple(10, 11, 8) },
    { std::make_tuple(3, 0, 9), std::make_tuple(3, 9, 11),
      std::make_tuple(11, 9, 10) },
    { std::make_tuple(0, 1, 10), std::make_tuple(0, 10, 8),
      std::make_tuple(8, 10, 11) },
    { std::make_tuple(3, 1, 10), std::make_tuple(11, 3, 10) },
    { std::make_tuple(1, 2, 11), std::make_tuple(1, 11, 9),
      std::make_tuple(9, 11, 8) },
    { std::make_tuple(3, 0, 9), std::make_tuple(3, 9, 11),
      std::make_tuple(1, 2, 9), std::make_tuple(2, 11, 9) },
    { std::make_tuple(0, 2, 11), std::make_tuple(8, 0, 11) },
    { std::make_tuple(3, 2, 11) },
    { std::make_tuple(2, 3, 8), std::make_tuple(2, 8, 10),
      std::make_tuple(10, 8, 9) },
    { std::make_tuple(9, 10, 2), std::make_tuple(0, 9, 2) },
    { std::make_tuple(2, 3, 8), std::make_tuple(2, 8, 10),
      std::make_tuple(0, 1, 8), std::make_tuple(1, 10, 8) },
    { std::make_tuple(1, 10, 2) },
    { std::make_tuple(1, 3, 8), std::make_tuple(9, 1, 8) },
    { std::make_tuple(0, 9, 1) },
    { std::make_tuple(0, 3, 8) },
    {}
};

inline const Vector3 pos_trlt[12] = { Vector3(0.5, 1, 1), Vector3(1, 0.5, 1),
                                      Vector3(0.5, 0, 1), Vector3(0, 0.5, 1),
                                      Vector3(0.5, 1, 0), Vector3(1, 0.5, 0),
                                      Vector3(0.5, 0, 0), Vector3(0, 0.5, 0),
                                      Vector3(0, 1, 0.5), Vector3(1, 1, 0.5),
                                      Vector3(1, 0, 0.5), Vector3(0, 0, 0.5) };

Object::Object(Material *material)
    : material(material)
{}

Object::~Object()
{}

struct NextObject Object::intersect(Vector3 origin, Vector3 vector)
{
    return { NULL, HUGE_VAL };
}

bool Object::contains(Vector3 point)
{
    return false;
}

Vector3 Object::normal(Vector3 point)
{
    return Vector3(HUGE_VAL, HUGE_VAL, HUGE_VAL);
}

struct MaterialInfo Object::getMaterialInfo(Vector3 point)
{
    return this->material->getMaterialInfo(point);
}

Sphere::Sphere(Material *material, Vector3 center, double radius)
    : Object(material)
{
    this->center = center;
    this->radius = radius;
}

struct NextObject Sphere::intersect(Vector3 origin, Vector3 vector)
{
    Vector3 op = this->center - origin;
    double eps = 1e-4;
    double b = op.dot(vector);
    double det = b * b - op.dot(op) + this->radius * this->radius;
    if (det < 0)
        return { this, 0 };
    else
        det = sqrt(det);
    return { this,
             b - det > eps ? b - det : (b + det > eps ? b + det : HUGE_VAL) };
}

bool Sphere::contains(Vector3 point)
{
    return (point - this->center).size() <= this->radius;
}

Vector3 Sphere::normal(Vector3 point)
{
    return point - this->center;
}

Triangle::Triangle(Material *material, Vector3 coord_a, Vector3 coord_b,
                   Vector3 coord_c)
    : Object(material)
{
    this->coord_a = coord_a;
    this->coord_b = coord_b;
    this->coord_c = coord_c;
}

struct NextObject Triangle::intersect(Vector3 origin, Vector3 vector)
{
    double eps = 1e-4;
    Vector3 ba = this->coord_a - this->coord_b;
    Vector3 bc = this->coord_c - this->coord_b;
    Vector3 h = vector.cross(bc);

    double a = ba.dot(h);
    if (a > -eps && a < eps)
        return { NULL, HUGE_VAL };

    double f = 1 / a;
    Vector3 bo = origin - this->coord_b;

    double u = f * bo.dot(h);
    if (u < 0 || u > 1)
        return { NULL, HUGE_VAL };

    Vector3 q = bo.cross(ba);

    double v = f * vector.dot(q);
    if (v < 0 || u + v > 1)
        return { NULL, HUGE_VAL };

    float t = f * bc.dot(q);
    if (t > eps)
        return { this, t };
    else
        return { NULL, HUGE_VAL };
}

Vector3 Triangle::normal(Vector3 point)
{
    Vector3 ba = this->coord_a - this->coord_b;
    Vector3 bc = this->coord_c - this->coord_b;
    return ba.cross(bc).norm();
}

Blob::Blob(Material *material, Vector3 origin, double size, int disc,
           double min, double ***poten)
    : Object(material)
{
    const double disc_size = size / disc;
    for (int i = 0; i < disc; ++i)
        for (int j = 0; j < disc; j++)
            for (int k = 0; k < disc; k++)
            {
                Vector3 o = origin
                    + Vector3(i * disc_size, j * disc_size, k * disc_size);
                double p0 = poten[i][j + 1][k + 1];
                double p1 = poten[i + 1][j + 1][k + 1];
                double p2 = poten[i + 1][j][k + 1];
                double p3 = poten[i][j][k + 1];
                double p4 = poten[i][j + 1][k];
                double p5 = poten[i + 1][j + 1][k];
                double p6 = poten[i + 1][j][k];
                double p7 = poten[i][j][k];
                int index = 0;
                if (p0 < min)
                    index |= 1;
                if (p1 < min)
                    index |= 2;
                if (p2 < min)
                    index |= 4;
                if (p3 < min)
                    index |= 8;
                if (p4 < min)
                    index |= 16;
                if (p5 < min)
                    index |= 32;
                if (p6 < min)
                    index |= 64;
                if (p7 < min)
                    index |= 128;
                for (std::tuple<int, int, int> triangle : triangle_pos[index])
                    this->triangles.push_back(new Triangle(
                        this->material,
                        o + pos_trlt[std::get<0>(triangle)] * disc_size,
                        o + pos_trlt[std::get<1>(triangle)] * disc_size,
                        o + pos_trlt[std::get<2>(triangle)] * disc_size));
            }
}

struct NextObject Blob::intersect(Vector3 origin, Vector3 vector)
{
    struct NextObject res = { NULL, HUGE_VAL };
    for (Triangle *triangle : triangles)
    {
        struct NextObject temp = triangle->intersect(origin, vector);
        if (temp.distance > 0 && temp.distance < res.distance)
        {
            res.distance = temp.distance;
            res.object = temp.object;
        }
    }

    return res;
}

Vector3 Blob::normal(Vector3 point)
{
    return Vector3();
}
