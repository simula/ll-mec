Low Latency MEC platform (LL-MEC)
======================================
## What is LL-MEC?
LL-MEC is a real-time Multi-access Edge Computing platform.
* The bulk of the code is written from scratch using C++ and currently supports x64 Linux systems.
* The implementation aims to support core network programmability coordinated with RAN real-time operation and provide flexible application programming environment at the network edge.
* LL-MEC is well suited to conduct proof-of-concept experiments.
* LL-MEC is designed to easily expand the control function as well as the supported OpenFlow rules.

## Library dependency
* libfluid (http://opennetworkingfoundation.github.io/libfluid/): libfluid is a library bundle that provides the basic features to implement an OpenFlow controller
* nlohmann/json (https://github.com/nlohmann/json): craft and parse JSON message
* Pistache (https://github.com/oktal/pistache): REST API framework
* spdlog (https://github.com/gabime/spdlog): logging

## Dependencies installation
    $ ./install_dependencies.sh

## Building instruction
#### Prerequisite
* CMake version 2.8 or newer
* GCC version 4.8.1 or newer (for c++11 support)

#### To build
    ./build_ll-mec.sh
    # the executable will be present in the same folder
    
    ./clean_ll-mec.sh
    # to clean

## Configuration example (llmec_config.json)
    {
      "llmec": {
        "address": "0.0.0.0",
        "port": 6653,
        "number_of_workers": 4,
        "secure_connection": false
      },
      "northbound_api": {
        "port": 9999
      },
      "gateway": {
        "mac": "00:24:9b:23:33:a6"
      },
      "ovs_switch": {
        "s1u_port": 2,
        "external_port": 1
      },
      "mp1_api": {
        "port": 8888,
        "mode": "flexran"    
      },
      "flexran": [
       {
        "address": "10.0.0.2",
        "port": 9999
       },
       {
        "address": "127.0.0.1",
        "port": 9999
       }
     ]
    }

## Usage example
    $ sudo ./ll-mec -h
    [2018-01-21 23:16:08] [info] Low Latency MEC platform
    [2018-01-21 23:16:08] [info] -h
    [2018-01-21 23:16:08] [info] 
    [2018-01-21 23:16:08] [info] 	This help
    [2018-01-21 23:16:08] [info] 
    [2018-01-21 23:16:08] [info] -c [CONFIG_PATH]
    [2018-01-21 23:16:08] [info] 
    [2018-01-21 23:16:08] [info] 	Load config file from [CONFIG_PATH]. Default config will loaded if not specified

    $ sudo ./ll-mec
    [2018-01-21 23:14:56] [info] Stats manager started
    [2018-01-21 23:14:56] [info] Server running (0.0.0.0:6653)
    [2018-01-21 23:15:00] [info] Switch id=0 started
    [2018-01-21 23:15:00] [info] Switch id=0 established
    [2018-01-21 23:15:00] [info] Switch id=0 installed default flow
    [2018-01-21 23:15:13] [info] Add UE: {"enb_ip":"192.168.0.3","imsi":"123456789012345","s1_dl_teid":4,"s1_ul_teid":3,"ue_id":1,"ue_ip":"172.16.0.2"}
    [2018-01-21 23:15:25] [info] Redirected UE id=1 from 192.168.12.3 to 192.168.12.1
    [2018-01-21 23:15:33] [info] No redirected traffic for UE id=1


## MP1 API
#### RNI APIs
###### Sending a request for PLMN information (Section 5.2.3 Sending a request for PLMN information, ETSI GS MEC 012 V1.1.1)
    curl -X GET http://127.0.0.1:8888/mp1/v1/rni/queries/plmn_info?app_ins_id=app01
    # result    
    {"appInId":"app01","ecgi":{"cellId":"0","plmn":{"mcc":"208","mnc":"93"}},"timeStamp":{"nanoSeconds":0,"seconds":1577836800}} 

###### Subscribe to RNI event notifications (RabEstSubscription) (Section 5.2.5.1 Subscribing to RNI event notifications, ETSI GS MEC 012 V1.1.1). A notification will be sent to the callbackref whenever a RAB bearer is established
    curl -X POST http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est -d '{"callbackReference":"http://10.0.0.1:8888/rni/v1/rni/notifications/rab_est/1","filterCriteriaAssocQci":{"appInsId": "app01", "associateId":{"type":"1", "value": "10.0.0.1"}, "plmn": {"mnc":"01", "mcc":"001"}, "cellId":"0x800000B", "qci":1}, "expiryDeadline":{"seconds":15700,"nanoSeconds":0 } }'
    # result
    {"_links":{"self":"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01"},"callbackReference":"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/1","expiryDeadline":{"nanoSeconds":0,"seconds":15700},"filterCriteria":{"appInsId":"app01","associateId":{"type":"1","value":"10.0.0.1"},"cellId":["0x800000B"],"plmn":{"mcc":"001","mnc":"01"},"qci":1}}
    
###### Get information of a RabEst subscription
    curl -X GET http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01
    # result  
    {"_links":{"self":"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01"},"callbackReference":"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/1","expiryDeadline":{"nanoSeconds":0,"seconds":15700},"filterCriteria":{"appInsId":"app01","associateId":{"type":"1","value":"10.0.0.1"},"cellId":["0x800000B"],"plmn":{"mcc":"001","mnc":"01"},"qci":1}}
    
###### Add a bearer to trigger a RabEst notification
    curl -X POST http://127.0.0.1:9998/bearer -d '{"eps_bearer_id":1, "imsi":"208950000000009", "s1_ul_teid":"0x3", "s1_dl_teid":"0x4", "ue_ip":"172.16.0.2", "enb_ip":"192.168.0.3"}'
    # result
    OK
    
As a result, MEC App will receive the a notification (Section 5.2.7 Receiving RNI event notifications about Radio Access Bearer
establishment, ETSI GS MEC 012 V1.1.1 ):
    {"associateId":{"type":1,"value":"172.0.0.2"},"ecgi":{"cellId":"123","mcc":"208","mnc":"95"},"erabId":4,"erabQosParameters":{"qci":0,"qosInformation":{"erabGbrDl":0,"erabGbrUl":0,"erabMbrDl":0,"erabMbrUl":0}},"tempUeId":{"mmec":"mmec","mtmsi":"mtmsi"},"timeStamp":{"nanoSeconds":0,"seconds":1577836800}}

###### Update a RabEstSubscription for event notifications (Section 5.2.5.3 Updating subscription for RNI event notifications, ETSI GS MEC 012 V1.1.1)
    curl -X PUT http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01 -d '{"callbackReference":"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/2","filterCriteriaAssocQci":{"appInsId": "app01", "associateId":{"type":"1", "value": "10.10.10.1"}, "plmn": {"mnc":"01", "mcc":"001"}, "cellId":"0x800000B", "qci":1}, "expiryDeadline":{"seconds":15700,"nanoSeconds":0 } }'
    # result
    {"_links":{"self":"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01"},"callbackReference":"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/2","expiryDeadline":{"nanoSeconds":0,"seconds":15700},"filterCriteria":{}}
 

###### Unscribe from an event notification (Delete subscription with SubId) (Section 5.2.5.4 Unsubscribing from RNI event notifications,ETSI GS MEC 012 V1.1.1)
    curl -X DELETE http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01
    # result
    RabEstSubscription has been deleted!
    
verify that this subscription exist
    curl -X GET http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01
    # result
    No RabEstSubscription with Id app01!

###### Get a list of subscriptions for RabEstSubscription
    curl -X GET http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est
    # result
    {"links":"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est","subscription":[{"SubscriptionType":1,"href":"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/2"}]}

#### MP1 Services APIs

###### Create a new service (Section 5.2.4 Service availability update and new service registration, MEC ETSI 011): a ServiceAvailabilitySubscriptionNotification will be sent to the subscribers (subscribed to this event) 
    curl -X POST http://0.0.0.0:8888/mp1/v1/services -d  '{"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}'
    # result
    {"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serInstanceId":"serviceId1","serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}
    
###### Get service's information by service intance (Section 5.2.5 Service availability query, ETSI MEC 011)
    curl -X GET -G http://0.0.0.0:8888/mp1/v1/services -d ser_instance_id="serviceId1"
    # result
    [{"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serInstanceId":"serviceId1","serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}]
    
###### Get service's information by service name (Section 5.2.5 Service availability query, ETSI MEC 011)
    curl -X GET -G http://0.0.0.0:8888/mp1/v1/services -d ser_name="PLMN_Information"
    # result
    [{"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serInstanceId":"serviceId1","serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}]
    
###### Get service's information by service category (Section 5.2.5 Service availability query, ETSI MEC 011)
    curl -X GET -G http://0.0.0.0:8888/mp1/v1/services -d ser_category_id="RNI"
    # result
    [{"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serInstanceId":"serviceId1","serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}]
    
###### Update a service (Section 5.2.4 Service availability update and new service registration, MEC ETSI 011)
    curl -X PUT http://0.0.0.0:8888/mp1/v1/services/serviceId1 -d  '{"serCategory":{"href":"catTEST","id":"RNI","name":"RNI","version":"version1"},"serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}'
    # result
    {"serCategory":{"href":"catTEST","id":"RNI","name":"RNI","version":"version1"},"serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}


#### MP1 Subscriptions APIs

###### Create a new service availability subscription (Section 5.2.6 Service availability notification subscription, MEC ETSI 011)
    curl -X POST http://0.0.0.0:8888/mp1/v1/applications/appInstanceId1/subscriptions -d '{"subscriptionType":"SerAvailabilityNotificationSubscription", "callbackReference":"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/", "_links":{"self":{"href":"/meMp1/example"}},"filteringCriteria":{"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"}}'
    # result
    {"_links":{"self":{"href":"/meMp1/example"}},"callbackReference":"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/","filteringCriteria":{"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"},"subscriptionType":"SerAvailabilityNotificationSubscription"}
    

###### Create a new application termination subscription (MEC ETSI 011)
    curl -X POST http://0.0.0.0:8888/mp1/v1/applications/appInstanceId1/subscriptions -d '{"subscriptionType":"AppTerminationNotificationSubscription", "callbackReference":"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/", "_links":{"self":{"href":"/meMp1/example"}}, "appInstanceId":"appInstance1"}'
    # result
    {"_links":{"self":{"href":"/meMp1/example"}},"appInstanceId":"appInstance1","callbackReference":"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/","subscriptionType":"AppTerminationNotificationSubscription"}
    


###### Get a list of all subscriptions (Section 7.6 Resource: all meMp1Subscriptions, MEC ETSI 011)
    curl -X GET http://0.0.0.0:8888/mp1/v1/applications/appInstanceId1/subscriptions
    # result
    {"_links":{"self":"0.0.0.0:8888/applications/appInstanceId1/subscriptions","subscription":[{"href":"0.0.0.0:8888/applications/appInstanceId1/subscriptions/SerAvailabilityNotificationSubscription/subscriptionappInstanceId1serAvailability1","rel":"SerAvailabilityNotificationSubscription"},{"href":"0.0.0.0:8888/applications/appInstanceId1/subscriptions/AppTerminationNotificationSubscription/subscriptionappInstanceId1appTermination2","rel":"AppTerminationNotificationSubscription"}]}}
    

###### Get an Application Termination Subscription's info (Section 7.6 Resource: all meMp1Subscriptions, MEC ETSI 011)
    curl -X GET http://0.0.0.0:8888/mp1/v1/applications/appInstanceId1/subscriptions/AppTerminationNotificationSubscription/subscriptionappInstanceId1appTermination1
    # result
    null
    

###### Get a Service Availability Subscription's info (Section 7.6 Resource: all meMp1Subscriptions, MEC ETSI 011)
    curl -X GET http://0.0.0.0:8888/mp1/v1/applications/appInstanceId1/subscriptions/SerAvailabilityNotificationSubscription/subscriptionappInstanceId1serAvailability1
    # result
    {"_links":{"self":{"href":"/meMp1/example"}},"callbackReference":"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/","filteringCriteria":{"serCategory":{"href":"catRNI","id":"RNI","name":"RNI","version":"version1"},"serName":"PLMN_Information","serializer":"JSON","state":null,"transportInfo":{"description":"REST API","endpoint":{"addresses":[{"host":"127.0.0.1","port":8888}],"uris":["mp1/v1/queries/plmn_info"]},"id":"TransId1","name":"REST","protocol":"HTTP","security":{"oAuth2Info":{"grantTypes":["OAUTH2_CLIENT_CREDENTIALS"],"tokenEndpoint":"/mp1/v1/security/TokenEndPoint"}},"type":"REST_HTTP","version":"2.0"},"version":"ServiceVersion1"},"subscriptionType":"SerAvailabilityNotificationSubscription"}
    

## Contact
Please email to Mosaic5G (mosaic5g@lists.eurecom.fr)
