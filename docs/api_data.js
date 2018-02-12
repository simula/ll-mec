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
        "content": "curl -X POST http://127.0.0.1:9999/bearer -d '{\"eps_bearer_id\":1, \"imsi\":\"208950000000009\", \"s1_ul_teid\":\"0x3\", \"s1_dl_teid\":\"0x4\", \"ue_ip\":\"172.16.0.2\", \"enb_ip\":\"192.168.0.3\"}'",
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
  }
] });
