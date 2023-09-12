# Bluetooth Serial protocol

```
-----------------------------
| Num | Value | Description |
-----------------------------
|  0  |  0x41 | Start byte  |
|  1  |  0xYY | Message ID  |
|  2  |  0xYY | Instruction |
| 3 - |  0xYY | Parameters  |
| n-1 |  0x0D | End byte 1  |
|  n  |  0x0A | End byte 2  |
-----------------------------
```

## Message ID

```
-----------------------
| Value | Description |
-----------------------
|  0x01 | Ping        |
|  0x02 | Settings    |
|  0x03 | Control     |
|  0x04 | Status      |
-----------------------
```

### Ping

```
-----------------------
| Value | Description |
-----------------------
|  0x01 | Ping        |
-----------------------
```

### Settings

```
-----------------------
| Value | Description |
-----------------------
| 0x01  | Throttle    |
-----------------------
```

#### Throttle

##### Parameter 0

```
---------------------------------
| Value | Description           |
---------------------------------
| 0x01  | Throttle min          |
| 0x02  | Throttle max          |
| 0x03  | Throttle save         |
---------------------------------
```

##### Parameter 1

```
--------------------------
| Value | Description    |
--------------------------
| 0x00  | Throttle value |
--------------------------
```
