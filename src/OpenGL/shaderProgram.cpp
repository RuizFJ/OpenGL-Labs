#include "ShaderProgram.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

void loadSource(const std::string& path, std::string& source) {
  std::ifstream input { path, std::ios::in };
  if (!input.is_open()) throw std::runtime_error("Cannot open file in the path: " + path);

  while (input.good()) {
    std::string temp;
    std::getline(input, temp, '\n');
    source += temp.append(1, '\n');
  }
}

void compileShader(GLuint shader) {
  glCompileShader(shader);

  char infoLog[512];
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Shader compilation failed:\n" << infoLog << '\n';
    throw std::runtime_error("Shader compilation failed");
  }
}

void linkShaderProgram(GLuint shaderProgram) {
  glLinkProgram(shaderProgram);
  char infoLog[512];

  int success;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    std::cerr << "Shader program linking failed:\n" << infoLog << '\n';
    throw std::runtime_error("Shader program linking failed");
  }
}

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
  loadSource(vertexShaderPath, vertexShaderSource);
  loadSource(fragmentShaderPath, fragmentShaderSource);

  GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  const char* vertSource_cstr = vertexShaderSource.c_str();
  const char* fragSource_cstr = fragmentShaderSource.c_str();

  glShaderSource(vertexShader, 1, &vertSource_cstr, nullptr);
  glShaderSource(fragmentShader, 1, &fragSource_cstr, nullptr);

  compileShader(vertexShader);
  compileShader(fragmentShader);

  programId = glCreateProgram();
  glAttachShader(programId, vertexShader);
  glAttachShader(programId, fragmentShader);
  linkShaderProgram(programId);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
  if (programId != 0) glDeleteProgram(programId);
}

void ShaderProgram::use() { glUseProgram(programId); }

void ShaderProgram::deleteprogram() {
  if (programId != 0) {
    glDeleteProgram(programId);
    programId = 0;
  }
}

void ShaderProgram::setFloat(const std::string& name, float value) {
  glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderProgram::setInt(const std::string& name, int value) {
  glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

GLuint ShaderProgram::Id() { return programId; }