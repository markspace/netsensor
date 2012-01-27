#!/bin/bash

# hobbitserver.cfg
#
# Add sensors=ncv to TEST2RRD
# NCV_sensors="Temperature:GAUGE,Light:GAUGE"
#
#
# hobbitgraph.cfg
# [sensors]
#     TITLE Sensors
#     YAXIS Units
#     DEF:temp=sensors.rrd:Temperature:AVERAGE
#     DEF:light=sensors.rrd:Light:AVERAGE
#     LINE2:temp#00CCCC:Celcius
#     LINE2:light#FF0000:Lux
#     COMMENT:\n
#     GPRINT:temp:LAST:Temp \: %4.2lf%s (cur)
#     GPRINT:temp:MAX: \: %4.2lf%s (max)
#     GPRINT:temp:MIN: \: %4.2lf%s (min)
#     GPRINT:temp:AVERAGE: \: %4.2lf%s (avg)\n
#     GPRINT:light:LAST:Light \: %5.2lf%s (cur)
#     GPRINT:light:MAX: \: %5.2lf%s (max)
#     GPRINT:light:MIN: \: %5.2lf%s (min)
#     GPRINT:light:AVERAGE: \: %5.2lf%s (avg)\n
# [netsensor-temp]
#     TITLE Temperature
#     YAXIS C
#     DEF:temp=sensors.rrd:Temperature:AVERAGE
#     LINE2:temp#00CCCC:Celcius
#     COMMENT:\n
#     GPRINT:temp:LAST:Temp \: %4.2lf%s (cur)
#     GPRINT:temp:MAX: \: %4.2lf%s (max)
#     GPRINT:temp:MIN: \: %4.2lf%s (min)
#     GPRINT:temp:AVERAGE: \: %4.2lf%s (avg)\n
# [netsensor-light]
#     TITLE Light
#     YAXIS Lux
#     DEF:light=sensors.rrd:Light:AVERAGE
#     LINE2:light#FF0000:Lux
#     COMMENT:\n
#     GPRINT:light:LAST:Light \: %5.2lf%s (cur)
#     GPRINT:light:MAX: \: %5.2lf%s (max)
#     GPRINT:light:MIN: \: %5.2lf%s (min)
#     GPRINT:light:AVERAGE: \: %5.2lf%s (avg)\n


data=`wget -q -O - http://192.168.100.87|cut -d ' ' -f 1-2`

$BB $BBDISP "status netsensor.sensors green `date`
$data
<a href=/xymon-cgi/hobbitgraph.sh?host=netsensor&service=netsensor-temp&graph_width=900&graph_height=200&disp=netsensor&nostale&color=green&graph=hourly&action=menu><img src=/xymon-cgi/hobbitgraph.sh?host=netsensor&service=netsensor-temp&graph_width=900&graph_height=200&disp=netsensor&nostale&color=green&graph=hourly&action=view border=0 alt=netsensor-temp></a><br>
<a href=/xymon-cgi/hobbitgraph.sh?host=netsensor&service=netsensor-light&graph_width=900&graph_height=200&disp=netsensor&nostale&color=green&graph=hourly&action=menu><img src=/xymon-cgi/hobbitgraph.sh?host=netsensor&service=netsensor-light&graph_width=900&graph_height=200&disp=netsensor&nostale&color=green&graph=hourly&action=view border=0 alt=netsensor-light></a><br>
"

exit 0
