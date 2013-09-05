/** \file generalOperator.h
    \brief Base class for all operators on which we can compute a gradient.
*/

#pragma once


#include "complext.h"

#include <boost/shared_ptr.hpp>
#include <vector>
#include <stdexcept>

namespace Gadgetron{

  template <class ARRAY> class generalOperator
  {
   public:

    typedef typename ARRAY::element_type ELEMENT_TYPE;
    typedef typename realType<ELEMENT_TYPE>::Type REAL;

    generalOperator() : weight_(REAL(1)){};

    generalOperator(std::vector<unsigned int> *dims) : weight_(REAL(1)){
      set_domain_dimensions(dims);
    }
    
    virtual ~generalOperator(){};

    /**
     * @brief Calculates the gradient of the operator at point "in"
     * @param[in] in Input point at which to calculate the gradient
     * @param[in,out] out Gradient
     * @param[in] accumulate If false, overrides the output array. Otherwise adds result.
     */
    virtual void gradient(ARRAY* in, ARRAY* out, bool accumulate = false ) = 0;
    

    /**
     * @brief Calculates the function value of the operator
     * @param[in] in Point at which to calculate the value
     * @return Function value at point "in"
     */
    virtual REAL magnitude(ARRAY* in)=0;


    /**
     * Set the domain dimension (image size) of the operator
     * @param[in] dims Domain dimensions
     */
    virtual void set_domain_dimensions( std::vector<unsigned int> *dims )
    {
      if( dims == 0x0 ) throw std::runtime_error("Null pointer provided");
      domain_dims_ = *dims;  
    }
    
    /**
     *
     * @return The domain dimensions (image size) of the operator
     */
    virtual boost::shared_ptr< std::vector<unsigned int> > get_domain_dimensions()
    {
      std::vector<unsigned int> *dims = new std::vector<unsigned int>();
      *dims = domain_dims_;
      return boost::shared_ptr< std::vector<unsigned int> >(dims);
    }
    
    /**
     * Sets the weight of the operator
     * @param[in] weight
     */
    virtual void set_weight( REAL weight ){ weight_ = weight; }

    /**
     *
     * @return Weight of the operator
     */
    virtual REAL get_weight(){ return weight_; }
    
    void* operator new (size_t bytes) { return ::new char[bytes]; }
    void operator delete (void *ptr) { delete [] static_cast <char *> (ptr); } 
    void * operator new(size_t s, void * p) { return p; }
    
  protected:
    REAL weight_;
    std::vector<unsigned int> domain_dims_;
  };  
}
