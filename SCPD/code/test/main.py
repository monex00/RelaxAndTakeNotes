import pandas as pd
import numpy as np
from sklearn.datasets import load_breast_cancer
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans
import seaborn as sns
from sklearn.decomposition import PCA
import plotly.express as px
import plotly.graph_objects as go

# Carica il dataset
data = load_breast_cancer()
df = pd.DataFrame(data.data, columns=data.feature_names)
df['diagnosis'] = data.target

# Standardizza i dati
scaler = StandardScaler()
scaled_features = scaler.fit_transform(df.drop('diagnosis', axis=1))

# Applica K-means
kmeans = KMeans(n_clusters=2, random_state=42)
clusters = kmeans.fit_predict(scaled_features)

# PCA per visualizzazione
pca = PCA(n_components=3)
components = pca.fit_transform(scaled_features)

# Crea DataFrame per visualizzazione
df_pca = pd.DataFrame(data=components, columns=['PC1', 'PC2', 'PC3'])
df_pca['Cluster'] = clusters
df_pca['Real_Diagnosis'] = df['diagnosis']

# Visualizzazione 3D interattiva
fig = px.scatter_3d(df_pca, 
                    x='PC1', y='PC2', z='PC3',
                    color='Cluster',
                    symbol='Real_Diagnosis',
                    title='Breast Cancer Clusters Analysis',
                    labels={'Cluster': 'Predicted Cluster',
                           'Real_Diagnosis': 'Actual Diagnosis'})

fig.update_layout(scene=dict(
    xaxis_title='Principal Component 1',
    yaxis_title='Principal Component 2',
    zaxis_title='Principal Component 3'),
    width=1000, height=800)

# Analisi delle caratteristiche più importanti
feature_importance = pd.DataFrame(
    {'feature': data.feature_names,
     'importance': np.abs(pca.components_[0])})
feature_importance = feature_importance.sort_values('importance', ascending=False)
plt.figure(figsize=(12, 8))

plt.show()

# Show the Plotly figure
fig.show()