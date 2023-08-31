#ifndef STATUSES_H_
#define STATUSES_H_

#include <stdio.h>
#include <assert.h>

/**
 * @brief Specifies functions status
 */
struct Status {
    enum Statuses {
        DEFAULT       = -2,  ///< Poison value
        NORMAL_WORK   = -1,  ///< Normal mode system value (isn't returned in main())
        OK_EXIT       =  0,  ///< OK and exit
        ARGS_ERROR    =  1,  ///< Console arguments error
        FILE_ERROR    =  2,  ///< File opening or reading error
        MEMORY_EXCEED =  3,  ///< Memory allocation failed
    };

    /**
     * @brief Prints and returns given status
     *
     * @param[in] status
     * @return Statuses
     */
    static Statuses raise(const Statuses status);
};


#endif // #ifndef STATUSES_H_
