// Copyright 2009 Micha�l Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_DESTROYER_H_
#define _CPPINJECT_DESTROYER_H_

namespace CppInject
{

/**
 * @internal
 * @brief Abtract functor to destroy an object in a given scope
 */
class destroyer
{
public:
	destroyer(){};
	virtual ~destroyer(){};
	
	virtual void operator()() = 0;
};

}
  
#endif
