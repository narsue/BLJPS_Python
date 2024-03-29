#pragma once
#include "Node.h"
using namespace std;
#include <vector>
enum AlgorithmType
{
	AT_ASTAR = 1,
	AT_JPS = 2,
	AT_BL_JPS = 4,
	AT_JPS_PLUS = 8,
	AT_BL_JPS_PLUS = 16,
	AT_UNKNOWN=2048,
	AT_ALL=0xFFFF,
};

class PathFindingAlgorithm
{
	private:
		string algorithmName;
		AlgorithmType algorithmType;
	protected:
		bool preprocessedData;
	public:
		PathFindingAlgorithm(string  _algorithmName,AlgorithmType id)
		{
			algorithmName=_algorithmName;
			algorithmType=id;
			preprocessedData=false;
		}
		virtual ~PathFindingAlgorithm()
		{
		}
		virtual void reProcessGrid(int lx,int rx,int ty,int by)
		{
		}
		virtual void preProcessGrid()
		{
		}
		virtual void flushReProcess()
		{
		}
		virtual int returnMemorySize()
		{
			return 0;
		}
		virtual void backupPreProcess()=0;
		virtual void useBackupData()=0;
		virtual vector<Coordinate> findSolution(int sX,int sY,int _eX,int _eY)=0;
		virtual bool isCoordinateBlocked(const Coordinate &c)=0;
		string getAlgorithmName()
		{
			return algorithmName;
		}
		AlgorithmType getAgorithmType()
		{
			return algorithmType;
		}
		virtual int getGridWidth()=0;
		virtual int getGridHeight()=0;
};