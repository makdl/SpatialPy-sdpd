#__all__=['model','spatialpy']
#from .spatialpy import *

import sys
if (sys.version_info < (3,0)):
    raise Exception("SpatialPy only works in Python 3.0 and higher")

from spatialpy.Model import *
from spatialpy.Solver import *
from spatialpy.Subdomain import *
from spatialpy.Mesh import *
from spatialpy.DataFunction import *
from spatialpy.InitialCondition import *
from spatialpy.VTKReader import *
