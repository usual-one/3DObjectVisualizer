#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <QColor>

// file formats
const std::string SURFACE_FILE_FORMAT = ".csv";

const std::string FIGURE_FILE_FORMAT = ".xml";

// exception messages
const std::string UNKNOWN_FORMAT_MESSAGE = "unknown file format";

const std::string EMPTY_MATRIX_MESSAGE = "matrix is empty";

const std::string EMPTY_VECTOR_MESSAGE = "vector is empty";

const std::string INVALID_MATRIX_MESSAGE = "matrix is invalid";

const std::string INVALID_SYSTEM_MESSAGE = "system is invalid";

const std::string UNKNOWN_TAG_MESSAGE = "unknown tag";

const std::string INVALID_VECTOR_MESSAGE = "vector is invalid";

const std::string OUT_OF_RANGE_MESSAGE = "out of range";

const std::string NOT_BASIS_MESSAGE = "vectors cannot form basis";

const std::string VERTEX_NOT_FOUND_MESSAGE = "vertex not found";

// surface
const std::string CSV_VALUE_SEPARATOR = ",";

const std::string CSV_LINE_SEPARATOR = "\n";

const std::string DEFAULT_SURFACE_TAG = "surface_";

const double DEFAULT_MAX_NEIGHBOUR_ANGLE = 83; // degrees (0; 90)

// figure
const std::string DEFAULT_FIGURE_TAG = "figure_";

const std::string DEFAULT_VERTEX_TAG = "vertex_";

// dialogs

// surface configuration dialog
const double MIN_SPBX_STEP_X = 0;

const double MAX_SPBX_STEP_X = 1000000;

const double MIN_SPBX_STEP_Y = 0;

const double MAX_SPBX_STEP_Y = 1000000;

const double MIN_SPBX_RANGE_MIN = -1000000;

const double MAX_SPBX_RANGE_MIN = 1000000;

const double MIN_SPBX_RANGE_MAX = -1000000;

const double MAX_SPBX_RANGE_MAX = 1000000;

// figure configuration dialog
const double MIN_COORD_VALUE = -1000000;

const double MAX_COORD_VALUE = 1000000;

// controls dialog
const double MIN_VALUE = -1000000;

const double MAX_VALUE = 1000000;

const double MOVE_VALUE_BEGIN = -100;

const double MOVE_VALUE_END = 100;

const double SCALE_VALUE_BEGIN = 0.01;

const double SCALE_VALUE_END = 2;

// export dialog
const std::string DEFAULT_FIGURES_DIR = "../3DSurfaceVisualizer/resource/";

// drawing
const QColor BACKGROUND_COLOR = Qt::white;

const QColor PEN_COLOR = Qt::black;

const int CANVAS_MARGIN = 10;

const size_t DEFAULT_DOT_RADIUS = 2; // pixels

// XML figure representation

const std::string XML_TAG_FIGURE = "Figure";

const std::string XML_TAG_VERTICES = "Vertices";

const std::string XML_TAG_VERTEX = "Vertex";

const std::string XML_TAG_POINT = "Point";//

const std::string XML_ATTRIBUTE_ID = "id";

const std::string XML_TAG_POSITION = "Position";

const std::string XML_ATTRIBUTE_X = "x";

const std::string XML_ATTRIBUTE_Y = "y";

const std::string XML_ATTRIBUTE_Z = "z";

const std::string XML_TAG_EDGES = "Edges";

const std::string XML_TAG_EDGE = "Edge";

const std::string XML_ATTRIBUTE_BEGIN = "begin";

const std::string XML_ATTRIBUTE_END = "end";

// context menus
const std::string MENU_ACTION_DELETE = "Delete";

#endif // CONFIG_H
