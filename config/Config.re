[@bs.val] external api_url: string = "process.env.API_URL";
[@bs.val]
external hasura_admin_key: string = "process.env.X_HASURA_ACCESS_KEY";
[@bs.val] external node_env: string = "process.env.NODE_ENV";

let is_production = node_env != "development";