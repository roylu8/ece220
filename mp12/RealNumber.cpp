/*
 * This block of code is what facilitates the creation of
 * real number for use in complex mathematics along with
 * imaginary numbers to allow for the use of magnitude and
 * phase.  These real numbers are solely comprised of 
 * decimal values.
 * 
 * Parters: roylu2, briolat2, kaylan4
 */


#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
  real_component = 0;
  magnitude = 0;
  phase = 0;
  number_type = REAL;
}

RealNumber::RealNumber(double rval)
{
  real_component = rval;
  magnitude = abs(rval);
  phase = calculate_phase(rval, 0);
  number_type = REAL;
}

RealNumber::RealNumber( const RealNumber& other )
{
  real_component = other.get_real_component();
  magnitude = other.get_magnitude();
  phase = other.get_phase();
  number_type = other.get_number_type();
}

void RealNumber::set_real_component (double rval)
{
  real_component = rval;
  magnitude = abs(rval);
  phase = calculate_phase(rval, 0);
}

double RealNumber::get_real_component() const
{
  return real_component;
}

double RealNumber::get_magnitude() const{
  return magnitude;
}

double RealNumber::get_phase() const{
  return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
  // 2 +-*/ 4
  return RealNumber(real_component + arg.get_real_component());
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
  return RealNumber(real_component - arg.get_real_component());
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
  return RealNumber(real_component * arg.get_real_component());
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
  return RealNumber(real_component / arg.get_real_component());
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
  // 2 +- 4i
  return ComplexNumber(real_component, + arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
  return ComplexNumber(real_component, - arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
  // 2 */ 4i
  return ImaginaryNumber(real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
  return ImaginaryNumber(-1 * real_component / arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
  // 2 +- <4,2>
  return ComplexNumber(real_component + arg.get_real_component(), + arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
  return ComplexNumber(real_component - arg.get_real_component(), + arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
  // 2 */ <4,2>
  return ComplexNumber(real_component * arg.get_real_component(), real_component * arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
  double den = (arg.get_real_component()*arg.get_real_component() + arg.get_imaginary_component()*arg.get_imaginary_component());
  double num_real = (real_component*arg.get_real_component());
  double num_imag = (real_component*-1*arg.get_imaginary_component());
  return ComplexNumber(num_real / den , num_imag / den);
}

string RealNumber::to_String(){
  /* Do not modify */
  stringstream my_output;
  my_output << std::setprecision(3) << real_component;
  return my_output.str();
}