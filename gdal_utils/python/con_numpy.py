import numpy as np
from osgeo import gdal
ds = gdal.Open("mypic.tif")
myarray = np.array(ds.GetRasterBand(1).ReadAsArray())
