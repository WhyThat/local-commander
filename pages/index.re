/* Handy for debug, but you won't always get what you expect out. Most useful
   with records, string, ints, float, etc. */
[@bs.val]
external prettyStringify:
  ('a, [@bs.as {json|null|json}] _, [@bs.as {json|2|json}] _) => string =
  "JSON.stringify";

let notEmptyValidator =
  fun
  | "" => Error("Ce champ ne doit pas etre vide")
  | value => Ok(value);

module SignupForm = [%form
  type input = {
    email: string,
    phoneNumber: string,
    fullname: string,
    password: string,
    collectPlace: string,
  };
  let validators = {
    email: {
      strategy: OnFirstSuccessOrFirstBlur,
      validate: ({email}) => {
        let emailRegex = [%bs.re {|/.*@.*\..+/|}];
        switch (email) {
        | "" => Error("Email is required")
        | _ as value when !emailRegex->Js.Re.test_(value) =>
          Error("Email is invalid")
        | _ => Ok(email)
        };
      },
    },
    phoneNumber: {
      strategy: OnFirstSuccessOrFirstBlur,
      validate: ({phoneNumber}) => notEmptyValidator(phoneNumber),
    },
    fullname: {
      strategy: OnFirstSuccessOrFirstBlur,
      validate: ({fullname}) => notEmptyValidator(fullname),
    },
    password: {
      strategy: OnFirstSuccessOrFirstBlur,
      validate: ({password}) => {
        let minLength = 4;
        switch (password) {
        | "" => Error("Mot de passe obligatoire")
        | _ when password->Js.String.length < minLength =>
          Error({j| $(minLength)+ characteres|j})
        | _ => Ok(password)
        };
      },
    },
    collectPlace: {
      strategy: OnFirstSuccessOrFirstBlur,
      validate: ({collectPlace}) => notEmptyValidator(collectPlace),
    },
  }
];

let initialInput: SignupForm.input = {
  email: "",
  phoneNumber: "",
  fullname: "",
  password: "",
  collectPlace: "",
};

module Style = {
  open TW;
  let mainClass =
    [
      BackgroundColor(BgGray400),
      MinHeight(MinHScreen),
      Display(Flex),
      FlexDirection(FlexCol),
    ]
    |> make;
  /* "container max-w-sm mx-auto flex-1 flex flex-col items-center justify-center px-2" */
  let containerClass =
    [
      Container,
      MaxWidth(MaxWSm),
      Display(Flex),
      FlexDirection(FlexCol),
      Flex(Flex1),
      Margin(MxAuto),
      AlignItems(ItemsCenter),
      JustifyContent(JustifyCenter),
    ]
    |> make;

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

  let buttonClass =
    [
      Width(WFull),
      TextAlign(TextCenter),
      TextColor(TextWhite),
      Padding(Py3),
      BorderRadius(Rounded),
      BackgroundColor(BgGreen400),
      BackgroundColor(HoverBgGreen600),
      OutlineNone,
    ]
    |> make;

  let linkClass =
    [TextDecoration(NoUnderline), TextColor(TextBlue400)] |> make;

  let cardClass =
    [
      BackgroundColor(BgWhite),
      Padding(Px6),
      Padding(Py8),
      BorderRadius(Rounded),
      BoxShadow(ShadowMd),
      TextColor(TextBlack),
      Width(WFull),
    ]
    |> make;

  let titleClass =
    [Margin(Mb8), FontSize(Text3xl), TextAlign(TextCenter)] |> make;
};
[@react.component]
let make = () => {
  let form =
    SignupForm.useForm(
      ~initialInput,
      ~onSubmit=(output, form) => {
        Js.log2("Submitted with:", output);
        Js.Global.setTimeout(
          () => {
            form.notifyOnSuccess(None);
            form.reset->Js.Global.setTimeout(3000)->ignore;
          },
          500,
        )
        ->ignore;
      },
    );
  <div className=Style.mainClass>
    <Form className=Style.containerClass onSubmit={form.submit}>
      <div className=Style.cardClass>
        <h1 className=Style.titleClass>
          "Creer un
                    compte"->React.string
        </h1>
        <Textfield
          value={form.input.fullname}
          name="fullname"
          placeholder="Nom complet"
          onBlur={form.blurFullname}
          onChange={
            form.updateFullname((input, value) =>
              {...input, fullname: value}
            )
          }
        />
        <Textfield
          value={form.input.email}
          name="email"
          placeholder="Email"
          onBlur={form.blurEmail}
          onChange={
            form.updateEmail((input, value) => {...input, email: value})
          }
        />
        <Textfield
          name="phoneNumber"
          placeholder="Numero de telephone"
          value={form.input.phoneNumber}
          onBlur={form.blurPhoneNumber}
          onChange={
            form.updatePhoneNumber((input, value) =>
              {...input, phoneNumber: value}
            )
          }
        />
        <input
          type_="text"
          value={form.input.collectPlace}
          className=Style.inputClass
          name="collectPlace"
          placeholder="Lieu de commande"
          onBlur={_ => form.blurCollectPlace()}
          onChange={event =>
            form.updateCollectPlace(
              (input, value) => {...input, collectPlace: value},
              event->ReactEvent.Form.target##value,
            )
          }
        />
        <input
          type_="password"
          value={form.input.password}
          className=Style.inputClass
          name="password"
          placeholder="Password"
          onBlur={_ => form.blurPassword()}
          onChange={event =>
            form.updatePassword(
              (input, value) => {...input, password: value},
              event->ReactEvent.Form.target##value,
            )
          }
        />
        <button type_="submit" className=Style.buttonClass>
          "Valider"->React.string
        </button>
      </div>
      <div
        className={[TW.TextColor(TextGray600), TW.Margin(Mt6)] |> TW.make}>
        "Vous avez deja un compte, "->React.string
        <a className=Style.linkClass href="../login/">
          "Connectez-vous"->React.string
        </a>
        "."->React.string
      </div>
    </Form>
  </div>;
};

let default = make;