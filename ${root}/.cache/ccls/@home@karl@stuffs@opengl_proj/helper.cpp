#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class Shader {
private:
    unsigned int id;
public:
    Shader(string vertexPath, string fragmentPath) {
        stringstream ss[2];
        ifstream files[2];
        files[0].open(vertexPath);
        files[1].open(fragmentPath);
        if (files[0].fail() || files[1].fail()) {
            cout << "Failed to open shader files" << endl;
            exit(1);
        }
        ss[0] << files[0].rdbuf();
        ss[1] << files[1].rdbuf();
        files[0].close();
        files[1].close();
        string codes[2] = {ss[0].str(), ss[1].str()};
        const char* shader_codes[2] = {codes[0].c_str(), codes[1].c_str()};
        unsigned int shader_ids[2];
        shader_ids[0] = glCreateShader(GL_VERTEX_SHADER);
        shader_ids[1] = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shader_ids[0], 1, &shader_codes[0], NULL);
        glShaderSource(shader_ids[1], 1, &shader_codes[1], NULL);

        int success;
        char infoLog[512];
        glCompileShader(shader_ids[0]);
        glGetShaderiv(shader_ids[0], GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_ids[0], 512, NULL, infoLog);
            cout << "Failed to compile vertex shader: " << infoLog << endl;
            exit(1);
        }
        glCompileShader(shader_ids[1]);
        glGetShaderiv(shader_ids[1], GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_ids[1], 512, NULL, infoLog);
            cout << "Failed to compile fragment shader: " << infoLog << endl;
            exit(1);
        }
        id = glCreateProgram();
        glAttachShader(id, shader_ids[0]);
        glAttachShader(id, shader_ids[1]);
        glLinkProgram(id);
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            cout << "Failed to link shader program: " << infoLog << endl;
            exit(1);
        }
        glDeleteShader(shader_ids[0]);
        glDeleteShader(shader_ids[1]);
    }

    void use() {
        glUseProgram(id);
    }
};
