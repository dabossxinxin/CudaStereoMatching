
FIND_PATH(GLEW_INCLUDE_DIRS NAMES GL HINTS C:/Program/glew-2.1.0/include)
FIND_PATH(GLEW_LIB_DIR NAMES glew32.lib HINTS C:/Program/glew-2.1.0/lib/Release/x64)
SET(GLEW_LIBRARIES ${GLEW_LIB_DIR}/glew32.lib)