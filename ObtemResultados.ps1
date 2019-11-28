#Dados
$grafos = dir grafo*.txt | Sort-Object -Property Length
$repeticoes = @(1000)

$dados = @()
$tempRepet = @()
[string[]]$tempDados = @()

foreach($grafo in $grafos) {
    Write-Host -ba Green -fo Black $grafo.Name "iniciou"
    foreach($repeticao in $repeticoes){
        Write-Host -ForegroundColor Magenta $repeticao "iniciou"
        $tempRepet += $repeticao
        $tempDados += .\bin\Debug\TC.exe $grafo.FullName $repeticao | Out-String
    }

    $dados += [PSCustomObject]@{"Ficheiro"=$Grafo.Name; "Repeticao"= $tempRepet; "Resultados" = $tempDados}

    #Prepara variaveis para a proxima iteracao
    $tempRepet = @()
    $tempDados = @()

    Write-Host -ForegroundColor Green $grafo.Name "Terminou"
}

clear;

write-host -BackgroundColor Yellow "------------------------------"
write-host -ForegroundColor Black "           Resultados         "
write-host -BackgroundColor Yellow "------------------------------"

foreach($dado in $dados){
    write-host -fo Black -BackgroundColor Green $dado.Ficheiro
    $temp = $dado.Resultados | findstr -i "Custo Final:" 
    write-host -fo Magenta $temp[-1]
    write-host -fo Magenta $($dado.Resultados | findstr -i MBF)
    write-host -fo black "----------------------------"

}