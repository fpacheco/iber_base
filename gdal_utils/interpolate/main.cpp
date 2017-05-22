#include <iostream>
#include <string>
//#include <boost/PrettyOptionPrinter.hpp>
#include <boost/program_options.hpp>
#include "boost/filesystem.hpp"
#include <gdal_priv.h>
#include <cpl_conv.h> // for CPLMalloc()

// Bilineal interpolation
#include "bilineal.hpp"

using namespace std;
using namespace boost::program_options;

namespace
{
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t SUCCESS = 0;
  const size_t ERROR_UNHANDLED_EXCEPTION = 2;

} // namespace

string gmshFile; //! name
string geoTifFile; //! name
int DX;
int DY;

int cmdParser(int argc, char *argv[]) {

  try {
    // Command options
    options_description desc{"Options"};
    desc.add_options()
        ("help,h", "Help screen")
        ("gmshfile,g", value<string>()->required(), "Gmsh file with initial mesh data")
        ("tiffile,t", value<string>()->required(), "GeoTIFF file with MDT (Z values) data");

    positional_options_description positionalOptions;
    positionalOptions.add("gmshfile", 1);
    positionalOptions.add("tiffile", 1);

    variables_map vm;

    try {
      // store(parse_command_line(argc, argv, desc), vm);
      store(command_line_parser(argc, argv).options(desc)
            .positional(positionalOptions).run(),
            vm);

      if (vm.count("help")) {
          cout << desc << '\n';
          return SUCCESS;
      }
      notify(vm); // throws on error, so do after help in case there are any problems
    } catch(boost::program_options::required_option& e) {
      //rad::OptionPrinter::formatRequiredOptionError(e);
      std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
      //rad::OptionPrinter::printStandardAppDesc(appName, std::cout, desc, &positionalOptions);
      return ERROR_IN_COMMAND_LINE;
    } catch(boost::program_options::error& e) {
      std::cerr << "ERROR: " << e.what() << std::endl;
      //rad::OptionPrinter::printStandardAppDesc(appName,std::cout,desc,&positionalOptions);
      return ERROR_IN_COMMAND_LINE;
    }

    if (vm.count("gmshfile") && vm.count("tiffile")) {
      gmshFile = vm["gmshfile"].as<string>();
      geoTifFile = vm["tiffile"].as<string>();
      cout << "gmshfile: " << gmshFile << endl;
      cout << "tiffile: " << geoTifFile << endl;
      return SUCCESS;
    }

  } catch (const error &ex) {
    cerr << "ERROR: " << ex.what() << endl;
    exit;
  }
}

int main(int argc, char *argv[])
{

  // Command line parser
  cmdParser(argc, argv);

  double adfGeoTransform[6];
  GDALDataset  *poDataset;
  GDALAllRegister();

  poDataset = (GDALDataset *) GDALOpen( geoTifFile.c_str(), GA_ReadOnly );

  if( poDataset == NULL )
  {
      return -1;
  }

  DX = poDataset->GetRasterXSize();
  DY = poDataset->GetRasterYSize();
  cout << "RASTER DX:" << DX << " RASTER DY:" << DY << endl;
  cout << "RASTER TOTAL BANDS:" << poDataset->GetRasterCount() << endl;

  if( poDataset->GetGeoTransform( adfGeoTransform ) == CE_None )
  {
      printf( "Origin = (%.6f,%.6f)\n",
              adfGeoTransform[0], adfGeoTransform[3] );
      printf( "Pixel Size = (%.6f,%.6f)\n",
              adfGeoTransform[1], adfGeoTransform[5] );
  }

  GDALRasterBand  *poBand;
  int             nBlockXSize, nBlockYSize;
  int             bGotMin, bGotMax;
  double          adfMinMax[2];
  poBand = poDataset->GetRasterBand( 1 );
  poBand->GetBlockSize( &nBlockXSize, &nBlockYSize );
  printf( "Block=%dx%d Type=%s, ColorInterp=%s\n",
          nBlockXSize, nBlockYSize,
          GDALGetDataTypeName(poBand->GetRasterDataType()),
          GDALGetColorInterpretationName(
              poBand->GetColorInterpretation()) );
  adfMinMax[0] = poBand->GetMinimum( &bGotMin );
  adfMinMax[1] = poBand->GetMaximum( &bGotMax );
  if( ! (bGotMin && bGotMax) )
      GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
  printf( "Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1] );
  if( poBand->GetOverviewCount() > 0 )
      printf( "Band has %d overviews.\n", poBand->GetOverviewCount() );
  if( poBand->GetColorTable() != NULL )
      printf( "Band has a color table with %d entries.\n",
               poBand->GetColorTable()->GetColorEntryCount() );

  float *pafScanline;
  int   nXSize = poBand->GetXSize();
  // static_cast<float *>
  pafScanline = (float *) CPLMalloc(sizeof(float)*nXSize);
  poBand->RasterIO( GF_Read, 0, 0, nXSize, 1, pafScanline, nXSize, 1, GDT_Float32, 0, 0 );
  /*
  for( int cont = 0; cont < nXSize; cont++) {
        cout << "value of pafScanline: " << pafScanline[cont] << endl;
  }
  */
  // Libero
  CPLFree(pafScanline);
  // Last close the dataset
  GDALClose(poDataset);
  return SUCCESS;
}
