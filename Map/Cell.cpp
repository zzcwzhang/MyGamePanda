#include "Cell.h"


std::vector<Cell*>Cell::g_cells;


Cell::Cell( int Num )
{
	//x第几列list; 
	//y第几行line;
	int line = Num/LIST_MAXCOUNT;
	int list = Num%LIST_MAXCOUNT;
	Pxy = ccp(list,line);
	CellRect = CCRectMake(list*ZC_RECTSIZE,line*ZC_RECTSIZE,ZC_RECTSIZE,ZC_RECTSIZE);
	curObject = eVoid;
	m_object = NULL;
}

Cell::Cell()
{
	static int i = 0;

	int line = i/LIST_MAXCOUNT;
	int list = i%LIST_MAXCOUNT;
	Pxy = ccp(list,line);
	CellRect = CCRectMake(list*ZC_RECTSIZE,line*ZC_RECTSIZE,ZC_RECTSIZE,ZC_RECTSIZE);
	curObject = eVoid;
	m_object = NULL;
	++i;
}

array1(Cell*) Cell::getCellarray()
{
	if (Cell::g_cells.size()==0)
	{
		Cell::g_cells.resize(144);
		for (int i = 0;i<Cell::g_cells.size();i++)
		{
			Cell::g_cells[i] = new Cell(i);
		}
	}

	return Cell::g_cells;
}

Cell::~Cell()
{
	//CCLog("111");
}

void Cell::deleteCells()
{
	for (int i = 0;i<Cell::g_cells.size();i++)
	{
		delete Cell::g_cells[i];
	}
}
