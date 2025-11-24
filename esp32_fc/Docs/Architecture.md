# Architecture

## Tasks

### Core 0 - Flight Dynamics:

- Sensor accquisition
- Data processing
- Control
- Actuators


### Core 1 - Comms and Storage:

- Radio task
- Logger Task
- GPS task
- Telemetry router task
- Health task
- Command handler task


### Explanation:
Control loop stays on same core as sensor aquisition for access as quickly as possible to new data. Also, Core 1 has a lot of writes + interrupts - need control to avoid any jitter, and be as deterministic as possible. Sensor acquisition is fast - just pushing data into queues.


## Queues

One for each sensor:
- __qIMU__
- __qBaro__
- __qGPS__

This is because we produce data faster than it can be consumed.

From this queue, the processing task runs, producing __qState__ (for control task) and __qTelemetry__ (for telemetry logging + transmission). __qTelemetry__ is stored in telemetry packets.

Packets from  __qTelemetry__  are sent out to __qRadioTx__ and __qLogger__, for their individual tasks to deal with


## Diagram

![Code diagram](../../Images/architectureDraft.drawio.svg)




