export default ({children}) => {
  return (
    <html>
        <head>
            <meta charset="UTF-8" />
            <title>Local commander</title>
            <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/tailwindcss/1.4.0/tailwind.min.css" />
        </head>
        <body>
          { children }
      </body>
    </html>);
}