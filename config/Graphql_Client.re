[@bs.module "node-fetch"] external fetch: ApolloClient.fetch = "default";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let authHeaders = Js.Dict.empty();
if (!Config.is_production) {
  Js.Dict.set(
    authHeaders,
    "x-hasura-admin-secret",
    Js.Json.string(Config.hasura_admin_key),
  );
};

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri=Config.api_url,
    ~headers=Js.Json.object_(authHeaders),
    ~fetch,
    (),
  );

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());