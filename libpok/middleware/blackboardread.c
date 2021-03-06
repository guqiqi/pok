/*
 *                               POK header
 * 
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team 
 *
 * Created by julien on Thu Jan 15 23:34:13 2009 
 */

#include <core/dependencies.h>

#ifdef POK_NEEDS_MIDDLEWARE
#ifdef POK_NEEDS_BLACKBOARDS
#include <errno.h>
#include <types.h>
#include <core/event.h>
#include <libc/string.h>
#include <middleware/blackboard.h>

extern pok_blackboard_t    pok_blackboards[POK_CONFIG_NB_BLACKBOARDS];
extern char                pok_blackboards_data[1024];


pok_ret_t pok_blackboard_read (const pok_blackboard_id_t   id, 
                               const uint64_t              timeout,
                               void*                       data,
                               pok_port_size_t*            len)
{
   (void) timeout;
   if (id > POK_CONFIG_NB_BLACKBOARDS)
   {
      return POK_ERRNO_EINVAL;
   }

   if (data == NULL)
   {
      return POK_ERRNO_EINVAL;
   }

   if (pok_blackboards[id].ready != TRUE)
   {
      return POK_ERRNO_EINVAL;
   }

   /* FIXME : Protect with mutexes when empty, ... */ 
   /* See what is the condition to use the timeout */

   pok_event_lock (pok_blackboards[id].lock);

   memcpy (data, &pok_blackboards_data[pok_blackboards[id].index], pok_blackboards[id].size);

   pok_event_unlock (pok_blackboards[id].lock);

   /* FIXME : return right size */
   *len = pok_blackboards[id].size;

   return POK_ERRNO_OK;
}

#endif
#endif
