define({ "api": [
  {
    "type": "Get",
    "url": "/services/:id",
    "title": "Get information of a service.",
    "name": "GetServiceID",
    "group": "MP1Services",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "serviceId",
            "description": "<p>Service Instance Id.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET -G http://127.0.0.1:8888/mp1/v1/services/serviceId1",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n\n{\"serCategory\":{\"href\":\"catRNI\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serInstanceId\":\"serviceId1\",\"serName\":\"PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/ServicesApi.cpp",
    "groupTitle": "MP1Services"
  },
  {
    "type": "Get",
    "url": "/services",
    "title": "Service availability query.",
    "name": "GetServices",
    "group": "MP1Services",
    "description": "<p>Either &quot;ser_instance_id&quot; or &quot;ser_name&quot; or &quot;ser_category_id&quot; shall be present.</p>",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "ser_instance_id",
            "description": "<p>List of ser_instance_ids to query the availability of a list of ME service instances.</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "ser_category_id",
            "description": "<p>Category Id to query the availability of ME services.</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "ser_name",
            "description": "<p>Names of service to be queried.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET -G http://127.0.0.1:8888/mp1/v1/services -d ser_instance_id=\"serviceId1\" -d ser_category_id=\"RNI1\" -d ser_name=\"PLMN Infomation\"",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n{\"serCategory\":{\"href\":\"catRNI\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serInstanceId\":\"serviceId1\",\"serName\":\"PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"}\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/ServicesApi.cpp",
    "groupTitle": "MP1Services"
  },
  {
    "type": "Post",
    "url": "/services",
    "title": "Create a service (new service registration).",
    "name": "PostServices",
    "group": "MP1Services",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "ServiceInfo",
            "optional": false,
            "field": "ServiceInfo",
            "description": "<p>(representing the general information of a ME service).</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X POST http://127.0.0.1:8888/mp1/v1/services -d  '{\"serCategory\":{\"href\":\"catRNI\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serName\":\"PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"}'",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n\n {\"serCategory\":{\"href\":\"catRNI\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serInstanceId\":\"serviceId1\",\"serName\":\"PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/ServicesApi.cpp",
    "groupTitle": "MP1Services"
  },
  {
    "type": "Put",
    "url": "/services",
    "title": "Update a ME service (service availability update).",
    "name": "PutServices",
    "group": "MP1Services",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "ServiceInfo",
            "optional": false,
            "field": "New",
            "description": "<p>ServiceInfo (representing the general information of a ME service).</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X PUT http://127.0.0.1:8888/mp1/v1/services/serviceId1 -d  '{\"serCategory\":{\"href\":\"New Category\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serName\":\"New PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"}'",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n\n{\"serCategory\":{\"href\":\"New Category\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serName\":\"New PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/ServicesApi.cpp",
    "groupTitle": "MP1Services"
  },
  {
    "type": "Delete",
    "url": "/applications/:appInstanceId/subscriptions/:subscriptionType/:subscriptionId",
    "title": "Delete a subscription",
    "name": "DeleteApplicationSubscription",
    "group": "Mp1Subscriptions",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "appInstanceId",
            "description": "<p>Id of the ME application.</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "subscriptionId",
            "description": "<p>Id of the subscription.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/subscriptions/AppTerminationNotificationSubscription/subscriptionappInstanceId1appTermination1",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/SubscriptionsApi.cpp",
    "groupTitle": "Mp1Subscriptions"
  },
  {
    "type": "Get",
    "url": "/applications/:appInstanceId/subscriptions/:subscriptionType/:subscriptionId",
    "title": "Retrieve information about a subscription for one specific app instance",
    "name": "GetApplicationSubscription",
    "group": "Mp1Subscriptions",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "appInstanceId",
            "description": "<p>Id of the ME application.</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "subscriptionType",
            "description": "<p>Represents a subscription type to the notifications from the ME platform (AppTerminationNotificationSubscription or SerAvailabilityNotificationSubscription).</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "subscriptionId",
            "description": "<p>Id of the subscription.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/subscriptions/AppTerminationNotificationSubscription/subscriptionappInstanceId1appTermination1",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n\n{\"_links\":{\"self\":{\"href\":\"/mp1/v1/applications/appInstanceId1\"}},\"appInstanceId\":\"appInstanceId1\",\"callbackReference\":\"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/\",\"subscriptionType\":\"AppTerminationNotificationSubscription\"}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/SubscriptionsApi.cpp",
    "groupTitle": "Mp1Subscriptions"
  },
  {
    "type": "Get",
    "url": "/applications/:appInstanceId/subscriptions",
    "title": "Retrieve information about all subscriptions for one specific app instance",
    "name": "GetApplicationSubscriptions",
    "group": "Mp1Subscriptions",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "appInstanceId",
            "description": "<p>Id of the ME application.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/subscriptions",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n\n{\"_links\":{\"self\":\"127.0.0.1:8888/applications/appInstanceId1/subscriptions\",\"subscription\":[{\"href\":\"127.0.0.1:8888/applications/appInstanceId1/subscriptions/SerAvailabilityNotificationSubscription/subscriptionappInstanceId1serAvailability1\",\"rel\":\"SerAvailabilityNotificationSubscription\"},{\"href\":\"127.0.0.1:8888/applications/appInstanceId1/subscriptions/AppTerminationNotificationSubscription/subscriptionappInstanceId1appTermination2\",\"rel\":\"AppTerminationNotificationSubscription\"}]}}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/SubscriptionsApi.cpp",
    "groupTitle": "Mp1Subscriptions"
  },
  {
    "type": "post",
    "url": "/applications/:appInstanceId/subscriptions",
    "title": "Create a subscription",
    "name": "SubscribeApplicationSubscription",
    "group": "Mp1Subscriptions",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "appInstanceId",
            "description": "<p>Id of the ME application.</p>"
          },
          {
            "group": "Parameter",
            "type": "SerAvailabilityNotificationSubscription",
            "optional": false,
            "field": "SerAvailabilityNotificationSubscription",
            "description": "<p>subscription to the ME service availability notifications.</p>"
          },
          {
            "group": "Parameter",
            "type": "AppTerminationNotificationSubscription",
            "optional": false,
            "field": "AppTerminationNotificationSubscription",
            "description": "<p>subscription to the ME application termination notifications.</p>"
          }
        ]
      }
    },
    "description": "<p>Ceate a new subscription to the ME service availability notifications (SerAvailabilityNotificationSubscription) or the ME application termination notifications (AppTerminationNotificationSubscription).</p>",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X POST http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/subscriptions -d '{\"subscriptionType\":\"SerAvailabilityNotificationSubscription\", \"callbackReference\":\"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/\", \"_links\":{\"self\":{\"href\":\"mp1/v1/applications/appInstanceId1\"}},\"filteringCriteria\":{\"serCategory\":{\"href\":\"catRNI\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serName\":\"PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"}}'\ncurl -X POST http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/subscriptions -d '{\"subscriptionType\":\"AppTerminationNotificationSubscription\", \"callbackReference\":\"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/\", \"_links\":{\"self\":{\"href\":\"mp1/v1/applications/appInstanceId1\"}}, \"appInstanceId\":\"appInstanceId1\"}'",
        "type": "curl"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n{\"_links\":{\"self\":{\"href\":\"mp1/v1/applications/appInstanceId1\"}},\"callbackReference\":\"http://127.0.0.1:8888/mp1/v1/applications/appInstanceId1/notifications/\",\"filteringCriteria\":{\"serCategory\":{\"href\":\"catRNI\",\"id\":\"RNI1\",\"name\":\"RNI\",\"version\":\"version1\"},\"serName\":\"PLMN Information\",\"serializer\":\"JSON\",\"state\":null,\"transportInfo\":{\"description\":\"REST API\",\"endpoint\":{\"addresses\":[{\"host\":\"127.0.0.1\",\"port\":8888}],\"uris\":[\"mp1/v1/queries/plmn_info\"]},\"id\":\"TransId1\",\"name\":\"REST\",\"protocol\":\"HTTP\",\"security\":{\"oAuth2Info\":{\"grantTypes\":[\"OAUTH2_CLIENT_CREDENTIALS\"],\"tokenEndpoint\":\"/mp1/v1/security/TokenEndPoint\"}},\"type\":\"REST_HTTP\",\"version\":\"2.0\"},\"version\":\"ServiceVersion1\"},\"subscriptionType\":\"SerAvailabilityNotificationSubscription\"}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/SubscriptionsApi.cpp",
    "groupTitle": "Mp1Subscriptions"
  },
  {
    "type": "delete",
    "url": "/rni/subscriptions/rab_est/:subscriptionId",
    "title": "Delete a RabEst subscription",
    "name": "DeleteRabEstSubscription",
    "group": "RNI",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "subscriptionId",
            "description": "<p>ID of the RabEstSubscription to be deleted.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/Mp1Api.cpp",
    "groupTitle": "RNI"
  },
  {
    "type": "get",
    "url": "/rni/queries/plmn_info",
    "title": "Get PLMN information",
    "name": "GetPLMNInfo",
    "group": "RNI",
    "description": "<p>Gets the information on Mobile Network(s) (PLMN info) associated with a specific application instance</p>",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "app_ins_id",
            "description": "<p>ME application instance's ID.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:8888/mp1/v1/rni/queries/plmn_info?app_ins_id=app01",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n\n  {\"appInId\":\"app01\",\"ecgi\":{\"cellId\":\"0\",\"plmn\":{\"mcc\":\"208\",\"mnc\":\"93\"}},\"timeStamp\":{\"nanoSeconds\":0,\"seconds\":1577836800}}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/Mp1Api.cpp",
    "groupTitle": "RNI"
  },
  {
    "type": "get",
    "url": "/rni/subscriptions/rab_est/:subscriptionId",
    "title": "Get information of a RabEst subscription",
    "name": "GetRabEstSubscription",
    "group": "RNI",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "subscriptionId",
            "description": "<p>ID of the RabEstSubscription.</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n{\"_links\":{\"self\":\"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01\"},\"callbackReference\":\"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/1\",\"expiryDeadline\":{\"nanoSeconds\":0,\"seconds\":15700},\"filterCriteria\":{\"appInsId\":\"app01\",\"associateId\":{\"type\":\"1\",\"value\":\"10.0.0.1\"},\"cellId\":[\"0x800000B\"],\"plmn\":{\"mcc\":\"001\",\"mnc\":\"01\"},\"qci\":1}}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/Mp1Api.cpp",
    "groupTitle": "RNI"
  },
  {
    "type": "get",
    "url": "/rni/subscriptions/rab_est/",
    "title": "Get a list of subscriptions for RabEstSubscription",
    "name": "GetRabEstSubscriptions",
    "group": "RNI",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n{\"links\":\"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est\",\"subscription\":[{\"SubscriptionType\":1,\"href\":\"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/2\"}]}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/Mp1Api.cpp",
    "groupTitle": "RNI"
  },
  {
    "type": "post",
    "url": "/rni/subscriptions/rab_est",
    "title": "Create a subscription to RAB establishment notifications",
    "name": "SubscribeRabEstSubscription",
    "group": "RNI",
    "description": "<p>Create a subscription to RAB establishment notifications from RNI Service</p>",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "URI",
            "optional": false,
            "field": "callbackReference",
            "description": "<p>(required) URL selected by the ME application to receive notifications on the subscribed RNIS information.</p>"
          },
          {
            "group": "Parameter",
            "type": "Structure",
            "optional": false,
            "field": "filterCriteria",
            "description": "<p>(required) (FilterCriteriaAssocQci) List of filtering criteria for the subscription</p>"
          },
          {
            "group": "Parameter",
            "type": "Structure",
            "optional": false,
            "field": "_links",
            "description": "<p>List of hyperlinks related to the resource</p>"
          },
          {
            "group": "Parameter",
            "type": "TimeStamp",
            "optional": false,
            "field": "expiryDeadline",
            "description": "<p>Time stamp</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X POST http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est -d '{\"callbackReference\":\"http://10.0.0.1:8888/rni/v1/rni/notifications/rab_est/1\",\"filterCriteriaAssocQci\":{\"appInsId\": \"app01\", \"associateId\":{\"type\":\"1\", \"value\": \"10.0.0.1\"}, \"plmn\": {\"mnc\":\"01\", \"mcc\":\"001\"}, \"cellId\":\"0x800000B\", \"qci\":1}, \"expiryDeadline\":{\"seconds\":15700,\"nanoSeconds\":0 } }'",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n{\"_links\":{\"self\":\"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01\"},\"callbackReference\":\"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/1\",\"expiryDeadline\":{\"nanoSeconds\":0,\"seconds\":15700},\"filterCriteria\":{\"appInsId\":\"app01\",\"associateId\":{\"type\":\"1\",\"value\":\"10.0.0.1\"},\"cellId\":[\"0x800000B\"],\"plmn\":{\"mcc\":\"001\",\"mnc\":\"01\"},\"qci\":1}}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/Mp1Api.cpp",
    "groupTitle": "RNI"
  },
  {
    "type": "put",
    "url": "/rni/subscriptions/rab_est:subscriptionId",
    "title": "Update a subscription to RAB establishment notifications",
    "name": "UpdateRabEstSubscription",
    "group": "RNI",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "URI",
            "optional": false,
            "field": "callbackReference",
            "description": "<p>(required) URL selected by the ME application to receive notifications on the subscribed RNIS information.</p>"
          },
          {
            "group": "Parameter",
            "type": "Structure",
            "optional": false,
            "field": "filterCriteria",
            "description": "<p>(required) (FilterCriteriaAssocQci) List of filtering criteria for the subscription</p>"
          },
          {
            "group": "Parameter",
            "type": "Structure",
            "optional": false,
            "field": "_links",
            "description": "<p>List of hyperlinks related to the resource</p>"
          },
          {
            "group": "Parameter",
            "type": "TimeStamp",
            "optional": false,
            "field": "expiryDeadline",
            "description": "<p>Time stamp</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "subscriptionId",
            "description": "<p>ID of the subscription</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X PUT http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01 -d '{\"callbackReference\":\"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/2\",\"filterCriteriaAssocQci\":{\"appInsId\": \"app01\", \"associateId\":{\"type\":\"1\", \"value\": \"10.10.10.1\"}, \"plmn\": {\"mnc\":\"01\", \"mcc\":\"001\"}, \"cellId\":\"0x800000B\", \"qci\":1}, \"expiryDeadline\":{\"seconds\":15700,\"nanoSeconds\":0 } }'",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n{\"_links\":{\"self\":\"http://127.0.0.1:8888/mp1/v1/rni/subscriptions/rab_est/app01\"},\"callbackReference\":\"http://10.0.0.1:8888/mp1/v1/rni/notifications/rab_est/2\",\"expiryDeadline\":{\"nanoSeconds\":0,\"seconds\":15700},\"filterCriteria\":{}}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "./src/mp1/api/Mp1Api.cpp",
    "groupTitle": "RNI"
  },
  {
    "success": {
      "fields": {
        "Success 200": [
          {
            "group": "Success 200",
            "optional": false,
            "field": "varname1",
            "description": "<p>No type.</p>"
          },
          {
            "group": "Success 200",
            "type": "String",
            "optional": false,
            "field": "varname2",
            "description": "<p>With type.</p>"
          }
        ]
      }
    },
    "type": "",
    "url": "",
    "version": "0.0.0",
    "filename": "./api-docs/main.js",
    "group": "_home_ubuntu_ll_mec_api_docs_main_js",
    "groupTitle": "_home_ubuntu_ll_mec_api_docs_main_js",
    "name": ""
  },
  {
    "success": {
      "fields": {
        "Success 200": [
          {
            "group": "Success 200",
            "optional": false,
            "field": "varname1",
            "description": "<p>No type.</p>"
          },
          {
            "group": "Success 200",
            "type": "String",
            "optional": false,
            "field": "varname2",
            "description": "<p>With type.</p>"
          }
        ]
      }
    },
    "type": "",
    "url": "",
    "version": "0.0.0",
    "filename": "./docs/main.js",
    "group": "_home_ubuntu_ll_mec_docs_main_js",
    "groupTitle": "_home_ubuntu_ll_mec_docs_main_js",
    "name": ""
  }
] });
