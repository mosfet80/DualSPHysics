//HEAD_DSPH
/*
 <DUALSPHYSICS>  Copyright (c) 2025 by Dr Jose M. Dominguez et al. (see http://dual.sphysics.org/index.php/developers/). 

 EPHYSLAB Environmental Physics Laboratory, Universidade de Vigo, Ourense, Spain.
 School of Mechanical, Aerospace and Civil Engineering, University of Manchester, Manchester, U.K.

 This file is part of DualSPHysics. 

 DualSPHysics is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License 
 as published by the Free Software Foundation; either version 2.1 of the License, or (at your option) any later version.
 
 DualSPHysics is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details. 

 You should have received a copy of the GNU Lesser General Public License along with DualSPHysics. If not, see <http://www.gnu.org/licenses/>. 
*/

/// \file JSphCfgRun.h \brief Declares the class \ref JSphCfgRun.

#ifndef _JSphCfgRun_
#define _JSphCfgRun_

#include "JCfgRunBase.h"
#include "DualSphDef.h"

//##############################################################################
//# JSphCfgRun
//##############################################################################
/// \brief Defines the class responsible for collecting the execution parameters by command line.

class JSphCfgRun : public JCfgRunBase
{
protected:
  int DirsDef;
  std::string FeatureList; ///<List of available features in current compilation.

public:
  bool Cpu;
  bool Gpu;
  int GpuId;
  bool Stable;
  int SvPosDouble;  ///<Saves particle position using double precision (default=0)
  std::string SvExtraParts;   ///<Part interval (or list) for saving extra data for restart option (default=empty=disabled)

  int OmpThreads;

  TpCellMode CellMode;  ///<Cell division mode.
  bool CellDomFixed;    ///<The Cell domain is fixed according maximum domain size (default=false).
  int TBoundary;        ///<Boundary method: -1:None, 1:DBC (by default), 2:mDBC (SlipMode: 1:DBC vel=0)
  int SlipMode;         ///<Slip mode for mDBC: -1:None, 1:DBC vel=0, 2:No-slip, 3:Free slip (default=1).
  bool NoPenetration;   ///<No Penetration for mDBC2.

  TpStep TStep;
  int VerletSteps;
  TpKernel TKernel;
  TpVisco TVisco;         ///<Viscosity type: Artificial,Laminar...
  float Visco;            ///<Viscosity value.
  float ViscoBoundFactor; ///<For boundary interaction use Visco*ViscoBoundFactor.

  double TimeMax;         ///<Total time to simulate [s].
  double TimePart;        ///<Time of output data [s].
  double TimePartExtra;   ///<Time for extra output data on motion and floating information (-1:Disabled) [s].

  double CFLnumber;       ///<Coefficient to multiply dt.
  int TDensity;           ///<Density Diffusion Term 0:None, 1:Molteni, 2:Fourtakas, 3:Fourtakas(full) (default=0)
  float DDTValue;         ///<Value used with Density Diffusion Term (default=0.1)
  double DDTValueTRamp;   ///<Total time of initial ramp for DDT value (default=0)  //<vs_ddramp>
  double DDTValueTMax;    ///<Time of maximum DDT value (default=0)                 //<vs_ddramp>
  double DDTValueMax;     ///<Maximum DDT value for initial ramp (default=0)        //<vs_ddramp>
  int Shifting;           ///<Shifting mode -1:no defined, 0:none, 1:nobound, 2:nofixed, 3:full
  bool ShiftAdvALE;       ///<Arbitrarian Eulerian-Lagrangian for Advanced shifting. //<vs_advshift>
  bool ShiftAdvNCP;       ///<Non conservative pressure for Advanced shifting.       //<vs_advshift>
  bool Sv_Binx,Sv_Info,Sv_Csv,Sv_Vtk;
  bool SvNormals; ///<Saves normals VTK each PART (default=0).
  bool SvRes;
  bool SvTimers;
  bool SvDomainVtk;
  std::string CaseName;
  std::string RunName;
  std::string DirOut;
  std::string DirDataOut;
  std::string PartBeginDir;
  unsigned PartBegin,PartBeginFirst;
  bool RestartChrono;             ///<Allows restart with Chrono active (default=0).
  float FtPause;
  bool RhopOutModif;              ///<Indicates whether \ref RhopOutMin or RhopOutMax is changed.
  float RhopOutMin,RhopOutMax;    ///<Limits for \ref RhopOut density correction.

  byte DomainMode;  ///<Domain configuration 0:No configured, 2:Fixed
  tdouble3 DomainFixedMin,DomainFixedMax;

  int NstepsBreak;  ///<Maximum number of steps allowed (debug).
  bool SvAllSteps;  ///<Saves a PART for each step (debug).
  bool NoRtimes;    ///<Removes execution dependent values from bi4 files (debug).

  unsigned PipsMode;   ///<Defines mode of PIPS calculation (0:No computed (default), 1:Computed, 2:computed and save detail).
  unsigned PipsSteps;  ///<Number of steps per interval to compute PIPS (100 by default).

#ifdef _WITHMR //<vs_vrres_ini>
  int   VRes;          ///<Define use of variable resolution zones (-1:Automatic, 0:Normal data, 1:VRes data).
  int   MRFastSingle;   
  int   VResOrder;
  int   VResMethod;
  float VResThreshold;
#endif         //<vs_vrres_end>

public:
  JSphCfgRun();
  void Reset();
  void SetFeatureList(std::string list){ FeatureList=list; }
  void VisuInfo()const;
  void VisuConfig()const;
  void LoadOpts(const std::string* optlis,int optn,int lv,const std::string& file);
  void ValidaCfg(){}
};

#endif

