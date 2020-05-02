open Jest;
open Expect;

describe("Test", () => {
  test("test", () => {
    expect(1 + 2) |> toEqual(3)
  })
});