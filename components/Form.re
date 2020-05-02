[@react.component]
let make = (~className, ~onSubmit, ~children) => {
  <form
    className
    onSubmit={event => {
      if (!event->ReactEvent.Form.defaultPrevented) {
        event->ReactEvent.Form.preventDefault;
      };
      Js.log("ok");
      onSubmit();
    }}>
    children
  </form>;
};