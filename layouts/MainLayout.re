module Link = Next.Link;

module Navigation = {
  [@react.component]
  let make = () => React.string("Local commander");
};

[@react.component]
let make = (~children) => {
  <>
    <Next.Head>
      <title> "Local commander"->React.string </title>
      <link
        rel="stylesheet"
        type_="text/css"
        href="https://cdnjs.cloudflare.com/ajax/libs/tailwindcss/1.4.0/tailwind.min.css"
      />
      <style>
        {j|
    #root {
      background-color:#e2e8f0;
      height: 100vh;
    }
      |j}
        ->React.string
      </style>
    </Next.Head>
    <main className="mt-4 mx-4"> children </main>
  </>;
};