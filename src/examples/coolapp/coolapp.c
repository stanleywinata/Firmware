#include <px4_log.h>
#include <px4_posix.h>
#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>

#include <uORB/uORB.h>
#include <uORB/topics/sensor_combined.h>
#include <uORB/topics/vehicle_attitude.h>
#include <uORB/topics/rams_flag.h>
__EXPORT int coolapp_main(int argc, char *argv[]);

int coolapp_main(int argc, char *argv[])
{
	PX4_INFO("GG my boi");
	// Subscribe to sensor_combined 'topic'
    int sensor_sub_fd = orb_subscribe(ORB_ID(sensor_combined));
    px4_pollfd_struct_t fds[] = {
           { .fd = sensor_sub_fd,   .events = POLLIN },
   };
   struct vehicle_attitude_s att;
   memset(&att, 0, sizeof(att));
   orb_advert_t att_pub = orb_advertise(ORB_ID(vehicle_attitude), &att);
   while (true) {

       if (fds[0].revents & POLLIN) {
	       /* obtained data for the first file descriptor */
	       struct sensor_combined_s raw;
           /* copy sensors raw data into local buffer */
           orb_copy(ORB_ID(sensor_combined), sensor_sub_fd, &raw);
           PX4_INFO("Accelerometer:\t%8.4f\t%8.4f\t%8.4f",
           (double)raw.accelerometer_m_s2[0],
           (double)raw.accelerometer_m_s2[1],
           (double)raw.accelerometer_m_s2[2]);
           orb_publish(ORB_ID(rams_flag), att_pub, &att);
       }
	}
}
