#ifndef DSS_hpp
#define DSS_hpp

#include <DGtal/base/Common.h>
#include <DGtal/io/boards/Board2D.h>
#include <DGtal/helpers/StdDefs.h>

typedef std::vector<DGtal::Z2i::Point>::const_iterator Iterator;
typedef DGtal::Circulator<Iterator> MyCirculator;

template <bool b> void detectContours(const DGtal::Z2i::Domain& d, const DGtal::Z2i::DigitalSet& forme, std::vector<DGtal::Z2i::Point>& out);

template <int c>
void maximalDSS(const std::vector<DGtal::Z2i::Point>& input, std::vector<DGtal::ArithmeticalDSSComputer< Iterator, DGtal::Z2i::Integer, c> >& output);

template <int c>
void DSScover(const std::vector<DGtal::Z2i::Point>& input, std::vector<DGtal::ArithmeticalDSSComputer< Iterator, DGtal::Z2i::Integer, c> >& output);

double DSSperimeter(const DGtal::Z2i::Domain& d, const DGtal::Z2i::DigitalSet& forme);



#endif /* DSS_hpp */
