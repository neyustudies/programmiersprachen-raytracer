#ifndef SDFPARSER_HPP
#define SDFPARSER_HPP

#include "scene.hpp"
#include <string>

/**
 * Read a scene from an SDF (Scene Description Format) file.
 */
Scene read_from_sdf(std::string const& filename);

#endif  // SDFPARSER_HPP
