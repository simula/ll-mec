## Description of the North-API

# The add default or dedicated bearer context API call
```
curl -X POST http://127.0.0.1:9999/bearer -d '{"eps_bearer_id":1, "imsi":"901700000000009", "s1_ul_teid":"0x3", "s1_dl_teid":"0x4", "ue_ip":"172.16.0.2", "enb_ip":"192.168.0.3"}'
```
Parameters of the call:

| Field	      	| Type   | Description 		                                            |
| ------------- | ------ | ---------------------------------------------------------  |
| eps_bearer_id | Number | EPS bearer ID		                                          |
| slice_id      | Number | (optional) SliceID.default=0        		                    |
| tos           | Number | (optional) TypeOfService including DSCP and ECN. default=0 |
| imsi          | String | IMSI							                                          |
| s1_ul_teid    | String | S1 downlink tunnel ID                                      |
| s1_dl_teild   | String | S1 downlink tunnel ID                                      |
| ue_ip         | String | IP address of UE                                           |
| enb_ip        | String | IP address of eNodeB                                       |
| meter_rate    | Number | (optional) Meter Bandwidth Rate.default=1000000kbps=1GBps  |
| burst_size    | Number | (optional) Meter Burst size.default=50000kbps=50Mbps       |


# GET all bearer context

```
curl -X GET http://127.0.0.1:9999/bearer

```
Response of the call:
```
HTTP/1.1 200 OK
[
  {
    "burst_size": 100000,
    "enb_ip": "192.168.0.3",
    "eps_bearer_id": 1,
    "id": 1,
    "imsi": "901700000000009",
    "meter_rate": 5000,
    "s1_dl_teid": 4,
    "s1_ul_teid": 3,
    "slice_id": 0,
    "tos": 0,
    "ue_ip": "172.16.0.2"
  }
]
```
# Get one specific bearer context By LLMEC-internally used bearer ID.
```
curl -X GET http://127.0.0.1:9999/bearer/id/1
```
| Field         | Type   | Description                                                                                                      |
| ------------- | ------ | ---------------------------------------------------------------------------------------------------------------  |
| id            | Number | ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)  |

# Redirect specific traffic flow for one bearer by IMSI and EPS bearer ID.
```
curl -X POST http://127.0.0.1:9999/bearer/redirect/imsi_bearer/901700000000009,1 -d '{"from":"192.168.12.3", "to":"192.168.12.1"}'
```
Parameters of the call:

| Field         | Type   | Description                                                												|
| ------------- | ------ | ---------------------------------------------------------  												|
| tos           | Number | (optional) TypeOfService including DSCP and ECN. default=0 												|
| from          | String | where the to-be-redirected traffic is coming from          												|
| to            | String | where the to-be-redirected traffic is going to             												|
| imsi_bearer   | String | ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)                                      |
