/*  Runner.h
 *
 *  Runner is a general class used to:
 *
 *  1) Initialize all the necessary classes
 *  2) get I/O
 *  3) run one or more cohort(s)
 *
 */

#ifndef RUNNER_H_
#define RUNNER_H_
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <map>

#ifdef WITHMPI
#include <mpi.h>
#endif


#include "../src/runmodule/Cohort.h"
#include "../src/runmodule/ModelData.h"
#include "CalController.h"
#include "ArgHandler.h"

using namespace std;

struct output_spec{
  std::string filename;
  bool veg;
  bool soil;
  int dim_count;
};

class Runner {
public:
  Runner(ModelData md, bool cal_mode, int y, int x);
  Runner();
  ~Runner();

  int y;
  int x;
  
  Cohort cohort;

  std::map<std::string, output_spec> monthly_netcdf_outputs;
  std::map<std::string, output_spec> yearly_netcdf_outputs;

  void check_sum_over_compartments();
  void check_sum_over_PFTs();
  void log_not_equal(const std::string& a_desc, const std::string& b_desc, int PFT, double A, double B);
 void log_not_equal(double A, double B, const std::string& msg);

  // Should end up as a null pointer if calibrationMode is off.
  boost::shared_ptr<CalController> calcontroller_ptr;
  int chtid;    /* currently-running 'cohort' id */
  int error;    /* error index */


  void run_years(int year_start, int year_end, const std::string& stage);
  void modeldata_module_settings_from_args(const ArgHandler &args);
  void output_caljson_yearly(int year, std::string, boost::filesystem::path p);
  void output_caljson_monthly(int year, int month, std::string, boost::filesystem::path p);
  void output_debug_daily_drivers(int iy, boost::filesystem::path p);

  //void output_netCDF(int year, boost::filesystem::path p);
  void create_netCDF_output_files(int ysize, int xsize);
  void output_netCDF_monthly(int year, int month);
  void output_netCDF_yearly();

private:
  bool calibrationMode;

  std::string loop_order;

  //data classes
  ModelData md;     /* model controls, options, switches and so on */

  // Unused?? as of 8/19/2015
  //EnvData  grded;   // grid-aggregated 'ed' (not yet done)
  //BgcData  grdbd;   // grid-aggregared 'bd' (not yet done)

  EnvData  chted;   // withing-grid cohort-level aggregated 'ed'
                    //   (i.e. 'edall in 'cht')
  BgcData  chtbd;
  FirData  chtfd;

  deque<RestartData> mlyres;

  void monthly_output(const int year, const int month, const std::string& runstage);
  void yearly_output(const int year, const std::string& stage, const int startyr, const int endyr);

};
#endif /*RUNNER_H_*/
