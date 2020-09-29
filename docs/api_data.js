define({ "api": [
  {
    "type": "get",
    "url": "/slice/:id",
    "title": "Get one indicated slice and its containing IDs (LLMEC internally-used ID)",
    "name": "GetSliceByID",
    "group": "Slice",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/slice/1",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n{\n  \"1\":[2]\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "Slice"
  },
  {
    "type": "get",
    "url": "/slice",
    "title": "Get all the slices and its containing IDs (LLMEC internally-used ID)",
    "name": "GetSlices",
    "group": "Slice",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/slice",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n{\n  \"1\":[2],\n  \"4\":[1]\n}",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "Slice"
  },
  {
    "type": "get",
    "url": "/stats",
    "title": "Get all the traffic flow statistic.",
    "name": "GetFlows",
    "group": "Stats",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/stats",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n  {\n    \"ul\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"dl\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"enb_ip\":\"192.168.0.1\",\n    \"eps_bearer_id\":2,\n    \"id\":2,\n    \"imsi\":\"208950000000001\",\n    \"s1_dl_teid\":51,\n    \"s1_ul_teid\":5,\n    \"slice_id\":1,\n    \"ue_ip\":\"172.16.0.5\"\n  },\n  {\n    \"ul\":{\n           \"byte_count\":0,\n           \"duration_sec\":12,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"dl\":{\n           \"byte_count\":0,\n           \"duration_sec\":12,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"enb_ip\":\"192.168.0.11\",\n    \"eps_bearer_id\":3,\n    \"id\":1,\n    \"imsi\":\"208950000000004\",\n    \"s1_dl_teid\":3,\n    \"s1_ul_teid\":6,\n    \"slice_id\":0,\n    \"ue_ip\":\"172.16.0.2\"\n  }\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/stats_rest_calls.cc",
    "groupTitle": "Stats"
  },
  {
    "type": "get",
    "url": "/stats/id/:id",
    "title": "Get the traffic flow statistic by ID. [Default]",
    "name": "GetFlowsByID",
    "group": "Stats",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/stats/id/2",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n  {\n    \"ul\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"dl\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"enb_ip\":\"192.168.0.1\",\n    \"eps_bearer_id\":2,\n    \"id\":2,\n    \"imsi\":\"208950000000001\",\n    \"s1_dl_teid\":51,\n    \"s1_ul_teid\":5,\n    \"slice_id\":1,\n    \"ue_ip\":\"172.16.0.5\"\n  }\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/stats_rest_calls.cc",
    "groupTitle": "Stats"
  },
  {
    "type": "get",
    "url": "/stats/:id",
    "title": "Get the traffic flow statistic by ID. [Default]",
    "name": "GetFlowsByID",
    "group": "Stats",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/stats/2",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n  {\n    \"ul\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"dl\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"enb_ip\":\"192.168.0.1\",\n    \"eps_bearer_id\":2,\n    \"id\":2,\n    \"imsi\":\"208950000000001\",\n    \"s1_dl_teid\":51,\n    \"s1_ul_teid\":5,\n    \"slice_id\":1,\n    \"ue_ip\":\"172.16.0.5\"\n  }\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/stats_rest_calls.cc",
    "groupTitle": "Stats"
  },
  {
    "type": "get",
    "url": "/stats/imsi_bearer/:imsi_bearer",
    "title": "Get the traffic flow statistic by IMSI and EPS bearer ID. [Default]",
    "name": "GetFlowsByIMSIandBearerID",
    "group": "Stats",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/stats/imsi_bearer/208950000000001,2",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n  {\n    \"ul\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"dl\":{\n           \"byte_count\":0,\n           \"duration_sec\":7,\n           \"packet_count\":0,\n           \"priority\":1,\n           \"table_id\":0\n         },\n    \"enb_ip\":\"192.168.0.1\",\n    \"eps_bearer_id\":2,\n    \"id\":2,\n    \"imsi\":\"208950000000001\",\n    \"s1_dl_teid\":51,\n    \"s1_ul_teid\":5,\n    \"slice_id\":1,\n    \"ue_ip\":\"172.16.0.5\"\n  }\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/stats_rest_calls.cc",
    "groupTitle": "Stats"
  },
  {
    "type": "post",
    "url": "/bearer",
    "title": "Add default/dedicated bearer context.",
    "name": "AddBearer",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "eps_bearer_id",
            "description": "<p>EPS bearer ID</p>"
          },
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "slice_id",
            "description": "<p>(optional) Slice ID. default = 0</p>"
          },
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "tos",
            "description": "<p>(optional) Type of service includeing DSCP and ECN. default = 0</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "imsi",
            "description": "<p>IMSI</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "s1_ul_teid",
            "description": "<p>S1 downlink tunnel ID</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "s1_dl_teid",
            "description": "<p>S1 uplink tunnel ID</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "ue_ip",
            "description": "<p>IP address of UE</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "enb_ip",
            "description": "<p>IP address of eNodeB</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X POST http://127.0.0.1:9999/bearer -d '{\"eps_bearer_id\":1,\"eps_meter_id\":2, \"imsi\":\"208950000000009\", \"s1_ul_teid\":\"0x3\", \"s1_dl_teid\":\"0x4\", \"ue_ip\":\"172.16.0.2\", \"enb_ip\":\"192.168.0.3\"}'",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "BadRequest",
            "description": "<p>Payload format error or empty.</p>"
          },
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "delete",
    "url": "/bearer/:id",
    "title": "Remove one specific bearer context [Default].",
    "name": "DeleteBearer",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:9999/bearer/1",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "delete",
    "url": "/bearer/id/:id",
    "title": "Remove one specific bearer context by LLMEC internally-used bearer ID.",
    "name": "DeleteBearerByID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:9999/bearer/id/1",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "delete",
    "url": "/bearer/imsi_bearer/:imsi_bearer",
    "title": "Remove one specific bearer context by its IMSI and EPS bearer ID.",
    "name": "DeleteBearerByIMSIandBearerID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "imsi_bearer",
            "description": "<p>IMSI and EPS bearer ID are concatenated by comma to from an indentity of bearer, e.g. 208950000000009,1</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:9999/bearer/imsi_bearer/208950000000009,1",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "delete",
    "url": "/bearer",
    "title": "Remove all bearers context.",
    "name": "DeleteBearers",
    "group": "User",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:9999/bearer",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "get",
    "url": "/bearer/id/:id",
    "title": "Get one specific bearer context By LLMEC-internally used bearer ID.",
    "name": "GetBearerByID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/bearer/id/1",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n {\"id\":1,\"enb_ip\":\"192.168.0.3\",\"imsi\":\"208950000000009\",\"eps_bearer_id\":5,\"s1_dl_teid\":4,\"s1_ul_teid\":3, \"tos\":0, \"slice_id\":0,\"eps_bearer_id\":1,\"ue_ip\":\"172.16.0.1\"}\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "get",
    "url": "/bearer/:id",
    "title": "Get one specific bearer context [Default].",
    "name": "GetBearerByID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/bearer/1",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n {\"id\":1,\"enb_ip\":\"192.168.0.3\",\"imsi\":\"208950000000009\",\"eps_bearer_id\":5,\"s1_dl_teid\":4,\"s1_ul_teid\":3, \"tos\":0, \"slice_id\":0,\"eps_bearer_id\":1,\"ue_ip\":\"172.16.0.1\"}\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "get",
    "url": "/bearer/imsi_bearer/:imsi_bearer",
    "title": "Get one specific bearer context by IMSI and EPS Bearer ID.",
    "name": "GetBearerByIMSIandBearerID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "imsi_bearer",
            "description": "<p>IMSI and EPS bearer ID are concatenated by comma to from an indentity of bearer, e.g. 208950000000009,1</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/bearer/imsi_bearer/208950000000009,1",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n {\"id\":1,\"enb_ip\":\"192.168.0.3\",\"imsi\":\"208950000000009\",\"eps_bearer_id\":5,\"s1_dl_teid\":4,\"s1_ul_teid\":3, \"tos\":0, \"slice_id\":0, \"eps_bearer_id\":1,\"ue_ip\":\"172.16.0.1\"}\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "get",
    "url": "/bearer",
    "title": "Get all bearer context.",
    "name": "GetBearers",
    "group": "User",
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X GET http://127.0.0.1:9999/bearer",
        "type": "json"
      }
    ],
    "success": {
      "examples": [
        {
          "title": "Success-Response:",
          "content": "HTTP/1.1 200 OK\n[\n {\"enb_ip\":\"192.168.0.3\",\"imsi\":\"208950000000009\",\"eps_bearer_id\":5,\"s1_dl_teid\":4,\"s1_ul_teid\":3, \"tos\":0, \"slice_id\":0,\"id\":1,\"ue_ip\":\"172.16.0.1\"},\n {\"enb_ip\":\"192.168.0.3\",\"imsi\":\"208950000000001\",\"eps_bearer_id\":5,\"s1_dl_teid\":2,\"s1_ul_teid\":1, \"tos\":0, \"slice_id\":0,\"id\":2,\"ue_ip\":\"172.16.0.2\"}\n]",
          "type": "json"
        }
      ]
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "post",
    "url": "/bearer/redirect/:id",
    "title": "Redirect specific traffic flow for one bearer. [Default]",
    "name": "RedirectBearer",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "tos",
            "description": "<p>(optional) Type of service includeing DSCP and ECN. default = 0</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "from",
            "description": "<p>where the to-be-redirected traffic is coming from</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "to",
            "description": "<p>where the to-be-redirected traffic is going to</p>"
          },
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X POST http://127.0.0.1:9999/bearer/redirect/1 -d '{\"from\":\"192.168.12.3\", \"to\":\"192.168.12.1\"}'",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "BadRequest",
            "description": "<p>Payload format error or empty.</p>"
          },
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "post",
    "url": "/bearer/redirect/id/:id",
    "title": "Redirect specific traffic flow for one bearer.",
    "name": "RedirectBearerByID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "tos",
            "description": "<p>(optional) Type of service includeing DSCP and ECN. default = 0</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "from",
            "description": "<p>where the to-be-redirected traffic is coming from</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "to",
            "description": "<p>where the to-be-redirected traffic is going to</p>"
          },
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X POST http://127.0.0.1:9999/bearer/redirect/id/1 -d '{\"from\":\"192.168.12.3\", \"to\":\"192.168.12.1\"}'",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "BadRequest",
            "description": "<p>Payload format error or empty.</p>"
          },
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "post",
    "url": "/bearer/redirect/imsi_bearer/:imsi_bearer",
    "title": "Redirect specific traffic flow for one bearer by IMSI and EPS bearer ID.",
    "name": "RedirectBearerByIMSIandBearerID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "tos",
            "description": "<p>(optional) Type of service includeing DSCP and ECN. default = 0</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "from",
            "description": "<p>where the to-be-redirected traffic is coming from</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "to",
            "description": "<p>where the to-be-redirected traffic is going to</p>"
          },
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "imsi_bearer",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X POST http://127.0.0.1:9999/bearer/redirect/imsi_bearer/208950000000009,1 -d '{\"from\":\"192.168.12.3\", \"to\":\"192.168.12.1\"}'",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "BadRequest",
            "description": "<p>Payload format error or empty.</p>"
          },
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "delete",
    "url": "/bearer/redirect/:id",
    "title": "Remove the redirect flow for one bearer. [Default]",
    "name": "RemoveRedirectBearer",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:9999/bearer/redirect/1",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "delete",
    "url": "/bearer/redirect/id/:id",
    "title": "Remove the redirect flow for one bearer by ID.",
    "name": "RemoveRedirectBearerByID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "Number",
            "optional": false,
            "field": "id",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:9999/bearer/redirect/id/1",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
  {
    "type": "delete",
    "url": "/bearer/redirect/imsi_bearer/:imsi_bearer",
    "title": "Remove the redirect flow for one bearer by IMSI and EPS bearer ID.",
    "name": "RemoveRedirectBearerByIMSIandBearerID",
    "group": "User",
    "parameter": {
      "fields": {
        "Parameter": [
          {
            "group": "Parameter",
            "type": "String",
            "optional": false,
            "field": "imsi_bearer",
            "description": "<p>ID of the bearer (LLMEC internally used to identify every single bearer, which is different from EPS bearer ID)</p>"
          }
        ]
      }
    },
    "examples": [
      {
        "title": "Example usage:",
        "content": "curl -X DELETE http://127.0.0.1:9999/bearer/redirect/imsi_bearer/208950000000009,1",
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
    "error": {
      "fields": {
        "Error 4xx": [
          {
            "group": "Error 4xx",
            "optional": false,
            "field": "ServiceUnavailable",
            "description": "<p>Switch connection lost.</p>"
          }
        ]
      }
    },
    "version": "0.0.0",
    "filename": "src/north_api/ue_rest_calls.cc",
    "groupTitle": "User"
  },
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
