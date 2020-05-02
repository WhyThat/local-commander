module Style = {
  open TW;
  let inputClass =
    [
      Display(Block),
      BorderWidth(Border),
      Margin(Mb4),
      BorderColor(BorderGray400),
      BorderRadius(Rounded),
      Width(WFull),
      Padding(P3),
    ]
    |> make;
};

[@react.component]
let make = (~onBlur, ~onChange, ~name, ~placeholder, ~type_="text", ~value) => {
  <input
    className=Style.inputClass
    name
    onBlur={_ => onBlur()}
    onChange={event => onChange(event->ReactEvent.Form.target##value)}
    placeholder
    type_
    value
  />;
};