import { App } from "astal/gtk3"
import style from "./style.scss"
import Bar from "./widget/Bar.tsx"
import Applauncher from "./widget/AppLauncher.tsx"

App.start({
    css: style,
    instanceName: "astal",
    requestHandler(request, res) {
        print(request)
        res("ok")
    },
    main: () => {
      App.get_monitors().map(Bar);
      Applauncher();
    }
})
