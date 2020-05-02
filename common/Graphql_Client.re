[@bs.module "node-fetch"] external fetch: ApolloClient.fetch = "default";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let authHeaders = Js.Dict.empty();
Js.Dict.set(authHeaders, "x-hasura-admin-secret", Js.Json.string(""));

let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="https://local-commander-stagging.herokuapp.com/v1/graphql",
    ~headers=Js.Json.object_(authHeaders),
    ~fetch,
    (),
  );

let instance =
  ReasonApollo.createApolloClient(~link=httpLink, ~cache=inMemoryCache, ());