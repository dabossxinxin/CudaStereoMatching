
FIND_PATH(FreeGlut_INCLUDE_DIR NAMES GL HINTS E:/Code/CUDAStereoMatching/SDK/glut/include)
FIND_PATH(FreeGlut_LIB_DIR NAMES freeglut.lib HINTS E:/Code/CUDAStereoMatching/SDK/glut/lib)
SET(FreeGlut_LIBRARY ${FreeGlut_LIB_DIR}/freeglut.lib)