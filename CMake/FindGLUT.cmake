
FIND_PATH(GLUT_INCLUDE_DIR NAMES glut.h HINTS E:/Code/CUDAStereoMatching/SDK/glut/include)
FIND_PATH(GLUT_LIB_DIR NAMES glut.lib HINTS E:/Code/CUDAStereoMatching/SDK/glut/lib)
SET(GLUT_LIBRARY ${GLUT_LIB_DIR}/glut.lib)