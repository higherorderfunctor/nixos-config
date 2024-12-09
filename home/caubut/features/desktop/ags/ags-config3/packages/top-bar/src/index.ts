 import style from "./style.scss"
 import { App } from "astal/gtk3"
import Bar from "./Widget/Bar.js"

App.start({
    css: style,
    instanceName: "astal",
    requestHandler(request, res) {
        print(request)
        res("ok")
    },
    main: () => {
      App.get_monitors().map(Bar);
    }
})
