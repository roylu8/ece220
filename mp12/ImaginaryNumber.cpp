/*
 * This code allows for the creation of imaginary numbers
 * which can then be used in complex math/with complex
 * numbers.  These imaginary numbers are of the form Ai
 * where A is a decimal value and i represents the
 * imaginary number.
 *  
 * Partners: roylu2, briolat2, kaylan4
 */


#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber()
{
  imaginary_component = 0;
  magnitude = 0;
  phase = 0;
  number_type = IMAGINARY;
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
  imaginary_component = rval;
  magnitude = abs(rval);
  phase = calculate_phase(0, rval);
  number_type = IMAGINARY;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
  imaginary_component = other.get_imaginary_component();
  magnitude = other.get_magnitude();
  phase = other.get_phase();
  number_type = other.get_number_type();
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
  imaginary_component = rval;
  magnitude = abs(rval);
  phase = calculate_phase(0, rval);
}

double ImaginaryNumber::get_imaginary_component() const
{
  return imaginary_component;
}

//Function for getting magnitude
double ImaginaryNumber::get_magnitude() const{
  return magnitude;
}

//Function for getting phase
double ImaginaryNumber::get_phase() const{
  return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
  return ImaginaryNumber(imaginary_component + arg.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
  return ImaginaryNumber(imaginary_component - arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
  return RealNumber(-1 * imaginary_component * arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
  return RealNumber(imaginary_component / arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
  return ComplexNumber(arg.get_real_component(), + imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
  return ComplexNumber(-1 * arg.get_real_component(), + imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
  return ImaginaryNumber(arg.get_real_component() * imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
  return ImaginaryNumber(imaginary_component / arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
  return ComplexNumber(arg.get_real_component(), + imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
  return ComplexNumber(-1 * arg.get_real_component(), + imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
  return ComplexNumber(-1 * imaginary_component * arg.get_imaginary_component(), imaginary_component * arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
  /* Your code here */
  double den = (arg.get_real_component()*arg.get_real_component() + arg.get_imaginary_component()*arg.get_imaginary_component());
  double num_imag = (imaginary_component*arg.get_real_component());
  double num_real = (imaginary_component*arg.get_imaginary_component());
  return ComplexNumber(num_real / den , num_imag / den);
}

string ImaginaryNumber::to_String(){
  /* Do not modify */
  stringstream my_output;
  my_output << std::setprecision(3) << imaginary_component << 'i';
  return my_output.str();
}