open ApolloHooks;

let getOrDefault = uuid =>
  uuid->Js.Json.decodeString->Belt.Option.getWithDefault("");
type user = {id: string};
module GetUsersQuery = [%graphql
  {|
    query GetUserList {
            user @bsRecord {
                id @bsDecoder(fn: "getOrDefault")
            }
        }
    |}
];

let useProposalsListQuery = () => useQuery(GetUsersQuery.definition);