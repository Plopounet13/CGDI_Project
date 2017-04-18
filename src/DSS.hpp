#ifndef DSS_hpp
#define DSS_hpp

#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>

typedef std::vector<Point>::const_iterator Iterator;
typedef Circulator<Iterator> MyCirculator;

template <bool b> void detectContours(const DigitalSet& forme, vector<Point>& out);

template <int c>
void maximalDSS(const vector<Point>& input, vector<ArithmeticalDSSComputer< Iterator, Integer, c> >& output);

template <int c>
void DSScover(const vector<Point>& input, vector<ArithmeticalDSSComputer< MyCirculator, Integer, c> >& output);








#endif /* DSS_hpp */
