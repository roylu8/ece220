
/*
 * This code creates a complex number of
 * real and imaginary numbers to allow for
 * arithmetic involving magnitude and phase.
 * 
 * Partners: roylu2, briolat2, kaylan4
 */

#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
  real_component = 0;
  imaginary_component = 0;
  magnitude = 0;
  phase =0;
  number_type = COMPLEX;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
  real_component = rval_real_component;
  imaginary_component = rval_imaginary_component;
  magnitude = sqrt((real_component*real_component) + (imaginary_component*imaginary_component));
  phase = calculate_phase(real_component, imaginary_component);
  number_type = COMPLEX;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
  real_component = other.get_real_component();
  imaginary_component = other.get_imaginary_component();
  magnitude = other.get_magnitude();
  phase = other.get_phase();
  number_type = other.get_number_type();
}

void ComplexNumber::set_real_component (double rval)
{
  real_component = rval;
  magnitude = sqrt((rval*rval) + (imaginary_component*imaginary_component));
  phase = calculate_phase(rval, imaginary_component);
}

double ComplexNumber::get_real_component() const
{
  return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
  imaginary_component = rval;
  magnitude = sqrt((real_component*real_component) + (rval*rval));
  phase = calculate_phase(real_component, rval);
}

double ComplexNumber::get_imaginary_component() const
{
  return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
  return magnitude;
}

double ComplexNumber::get_phase() const{
  return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
  return ComplexNumber(real_component + arg.real_component, imaginary_component + arg.imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
  return ComplexNumber(real_component - arg.real_component, imaginary_component - arg.imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
  return ComplexNumber(((real_component * arg.real_component)+(-1*imaginary_component * arg.imaginary_component)), ((real_component * arg.imaginary_component) + (imaginary_component * arg.real_component)));
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
  double den = (arg.get_real_component()*arg.get_real_component() + arg.get_imaginary_component()*arg.get_imaginary_component());
  double num_real = (real_component*arg.get_real_component() + imaginary_component*arg.get_imaginary_component());
  double num_imag = (real_component*-1*arg.get_imaginary_component() + imaginary_component*arg.get_real_component());
  return ComplexNumber(num_real / den , num_imag / den);
}


ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
  // (a,b) + c = (a+c, b)
  return ComplexNumber(real_component + arg.get_real_component(), imaginary_component + 0);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
  return ComplexNumber(real_component - arg.get_real_component(), imaginary_component - 0);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
  // (a,b) * c = (ac, cb)
  return ComplexNumber(real_component * arg.get_real_component(), imaginary_component * arg.get_real_component());
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
  // (a,b) / c = (a/c, b/c)
  return ComplexNumber(real_component / arg.get_real_component(), imaginary_component / arg.get_real_component());
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
  return ComplexNumber(real_component + 0, imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
  return ComplexNumber(real_component - 0, imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
  // (a,b) * ci = (i^2*bc, a*ci)
  return ComplexNumber(-1 * imaginary_component * arg.get_imaginary_component(), real_component * arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
  // (a,b) / ci = ()
  return ComplexNumber(imaginary_component / arg.get_imaginary_component(), -1 * real_component / arg.get_imaginary_component());
}

string ComplexNumber::to_String(){
  /* Do not modify */
  stringstream my_output;
  if (imaginary_component > 0)
    my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
  else if (imaginary_component < 0)
    my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
  else
    my_output << std::setprecision(3) << real_component;
  
  return my_output.str();
}