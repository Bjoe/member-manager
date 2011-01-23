/*
 * Executor.h
 *
 *  Created on: Sep 26, 2010
 *      Author: joerg
 */

#ifndef HANDLER_H_
#define HANDLER_H_

namespace ClubFrontendTest
{

class Handler
{
public:
    Handler()
    {
    }
    virtual ~Handler()
    {
    }

    virtual void handle() = 0;
};

}

#endif /* HANDLER_H_ */
