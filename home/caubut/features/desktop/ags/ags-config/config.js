import { Bar } from "./Bar.js"
import { AppLauncher } from "./AppLauncher.js"

App.config({
    style: "./style.css",
    windows: [
        Bar(),
        AppLauncher,

        // you can call it, for each monitor
        // Bar(0),
        // Bar(1)
    ],
})

export { }
