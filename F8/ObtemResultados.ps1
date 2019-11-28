#Dados
$grafos = dir grafo*.txt | Sort-Object -Property Length
$repeticoes = @(100,1000,5000)

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